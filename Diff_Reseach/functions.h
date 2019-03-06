#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<math.h>
#include"variables.h"
#include"DiffTableAndTransTable.h"
#define _CRT_SECURE_NO_WARNINGS

void TravRound1(int s_num);
void TravSbox2(int round, int num);
void TravSbox3(int a, int j, int round);
void TravSbox1_1();
void TravRound2(int s_num1);
void TravSbox2_1();
void Trav_out(int i, int n);
void TravRound3toR(int round, int s_num2);
void Round1();
void Round2();
void Round3toR(int n, int i, double multipro);
void LastRound(int round, double multipro);

void Max_p(ElemType s_in, ElemType &s_out, int num, double &p);
void Max_pro(ElemType s_in[8], ElemType s_out[8], double p[8]);
void InitSbox(int round, int a, int b[9], int c);
void SelectInDiff(ElemType a[8], ElemType b[8], int c[9], int sum, int i, int round);
ElemType s_box(ElemType input, ElemType s[4][16]);
ElemType SboxInDiff(ElemType a[8], ElemType b[8], int i);
double MultiPro(double a[8], int k);
void BitSplit(u64 a, ElemType b[8]);
u32 BitMerge(ElemType a[8]);
u32 Permute(ElemType a[8]);
u64 Extend(u32 a);
u32 InvExtend(ElemType a[8], ElemType b[8]);

//第一轮
void Round1() {
	double temp_p1;
	for (int i = 0; i <= 8; i++) {
		s[0][0] = -1;
		for (int j = 1; j <= 8; j++) s[0][j] = 0;
		temp_p1 = log2(pow(0.25, i));
		if (temp_p1 + B[r - 2] >= B[r - 1]) TravRound1(i);
	}
}
void TravRound1(int s_num) {
	switch (s_num)
	{
	case 0:
		p[0] = log2(1.0);
		X[0] = 0x00000000;
		for (int i = 0; i < 8; i++) {
			x[0][i] = 0;
			y[0][i] = 0;
			fr[0][i] = 0;
			mid[0][i] = 0;
		}
		if (p[0] + B[r - 2] >= B[r - 1]) Round2();
		break;
	case 1:
		TravSbox1_1();
		break;
		
	case 2:
		for (s[0][1] = 0; s[0][1] < 7; s[0][1]++) {
			for (s[0][2] = s[0][1] + 1; s[0][2] < 8; s[0][2]++) {
				for (int k = 0; k < 8; k++) InitSbox(0, k, s[0], 2);
				if ((s[0][1] + 1 != s[0][2]) && (s[0][1] != (s[0][2] + 1) % 8)) TravSbox2(0, 0);
				else if (s[0][1] == 0 && s[0][2] == 7) TravSbox2(0, 1);
				else TravSbox2(0, 2);
			}
		}
	default:
		TravSbox3(s_num, 1, 0);
		break;
	}
}

//第二轮
void Round2() {
	double temp_p2;
	for (int i = 0; i <= 8; i++) {
		s[1][0] = -1;
		for (int j = 1; j <= 8; j++) s[1][j] = 0;
		temp_p2 = log2(pow(0.25, i));
		if (temp_p2 + p[0] + B[r - 3] >= B[r - 1]) TravRound2(i);
	}
}
void TravRound2(int s_num1) {
	switch (s_num1)
	{
	case 0:
		if (p[0] != log2(1.0)) {
			for (int i = 0; i < 8; i++) {
				x[1][i] = 0;
				y[1][i] = 0;
				fr[1][i] = 0;
				mid[1][i] = 0;
			}
			p[1] = log2(1.0);
			temp[1] = p[0] + p[1];
			X[1] = 0x00000000;
			Y[1] = Permute(y[1]);
			X[2] = X[0] ^ Y[1];
			Round3toR(r, 3, temp[1]);
		}
		break;

	case 1:
		TravSbox2_1();
		break;
		
	case 2:
		for (s[1][1] = 0; s[1][1] < 7; s[1][1]++) {
			for (s[1][2] = s[1][1] + 1; s[1][2] < 8; s[1][2]++) {
				for (int k = 0; k < 8; k++) InitSbox(1, k, s[1], 2);
				if ((s[1][1] + 1 != s[1][2]) && (s[1][1] != (s[1][2] + 1) % 8)) TravSbox2(1, 0);
				else if (s[1][1] == 0 && s[1][2] == 7) TravSbox2(1, 1);
				else TravSbox2(1, 2);
			}
		}
		break;
		
	default:
		TravSbox3(s_num1, 1, 1);
		break;
	}

}

//递归遍历s盒输出，从i到n
void Trav_out(int i, int n) {
	for (y[1][s[1][i]] = 0; y[1][s[1][i]] < 16; y[1][s[1][i]]++) {
		if (P[s[1][i]][x[1][s[1][i]]][y[1][s[1][i]]] > -6) {
			pro[1][s[1][i]] = P[s[1][i]][x[1][s[1][i]]][y[1][s[1][i]]];
			p[1] = MultiPro(pro[1], 8);

			if (p[0] + p[1] + B[r - 3] >= B[r - 1]) {
				if (i < n) Trav_out(i + 1, n);
				else {
					temp[1] = p[0] + p[1];
					Y[1] = Permute(y[1]);
					X[2] = X[0] ^ Y[1];
					Round3toR(r, 3, temp[1]);
				}
			}
		}
	}
}
//第三轮至R轮
void Round3toR(int n, int i, double multipro) {
	Temp[i - 1] = Extend(X[i - 1]);
	BitSplit(Temp[i - 1], x[i - 1]);
	
	for (int j = 0; j < 8; j++) Max_p(x[i - 1][j], y[i - 1][j], j, pro[i - 1][j]);
	p[i - 1] = MultiPro(pro[i - 1], 8);
	if (p[i - 1] + multipro + B[r - 1 - i] >= B[r - 1]) TravRound3toR(i, 0);
}
//
void TravRound3toR(int round, int s_num2) {
	if (s_num2 <= 7) {
		if(x[round - 1][s_num2] == 0) TravRound3toR(round, s_num2 + 1);
		else {
			for (y[round - 1][s_num2] = 0; y[round - 1][s_num2] < 16; y[round - 1][s_num2]++) {
				if (P[s_num2][x[round - 1][s_num2]][y[round - 1][s_num2]] > -6) {
					pro[round - 1][s_num2] = P[s_num2][x[round - 1][s_num2]][y[round - 1][s_num2]];
					temp3 = MultiPro(pro[round - 1], 8);
					if (temp3 + temp[round - 2] + B[r - 1 - round] >= B[r - 1]) TravRound3toR(round, s_num2 + 1);
				}
			}
		}
	}
	else {
		p[round - 1] = MultiPro(pro[round - 1], 8);
		temp[round - 1] = p[round - 1] + temp[round - 2];
		Y[round - 1] = Permute(y[round - 1]);
		X[round] = Y[round - 1] ^ X[round - 2];
		if (round < r - 1) Round3toR(r, round + 1, temp[round - 1]);
		else LastRound(r, temp[r - 2]);
	}
}

//最后一轮
void LastRound(int round, double multipro)
{
	Temp[round - 1] = Extend(X[round - 1]);
	BitSplit(Temp[round - 1], x[round - 1]);

	for (int m = 0; m < 8; m++) Max_p(x[round - 1][m], y[round - 1][m], m, pro[round - 1][m]);
	p[round - 1] = MultiPro(pro[round - 1], 8);
	if (p[round - 1] + multipro >= B[round - 1]) {
		B[round - 1] = p[round - 1] + multipro;
		for (int i = 0; i < round; i++) {
			printf("Round: %2d, ", i);
			fprintf(fp, "Round: %2d, ", i);
			printf("Input: %2x %2x %2x %2x %2x %2x %2x %2x , ", x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7]);
			fprintf(fp, "Input: %2x %2x %2x %2x %2x %2x %2x %2x , ", x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7]);
			printf("Output: %2x %2x %2x %2x %2x %2x %2x %2x , ", y[i][0], y[i][1], y[i][2], y[i][3], y[i][4], y[i][5], y[i][6], y[i][7]);
			fprintf(fp, "Output: %2x %2x %2x %2x %2x %2x %2x %2x , ", y[i][0], y[i][1], y[i][2], y[i][3], y[i][4], y[i][5], y[i][6], y[i][7]);
			printf("Pro: 2^(%f)\n", p[i]);
			fprintf(fp, "Pro: 2^(%f)\n", p[i]);
		}
		printf("The best differential characteristic probability is 2^(%f) \n", B[round - 1]);
		fprintf(fp, "The best differential characteristic probability is 2^(%f) \n", B[round - 1]);
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
	}
}

void Max_p(ElemType s_in, ElemType &s_out, int num, double &p) {
	double max = -6;
	ElemType max_out;
	for (ElemType i = 0; i < 16; i++) {
		if (max <= P[num][s_in][i])
		{
			max = P[num][s_in][i];
			max_out = i;
		}

	}
	s_out = max_out;
	p = max;
}
// 当轮所有s盒的最大概率
void Max_pro(ElemType s_in[8], ElemType s_out[8], double p[8]) {
	for (int i = 0; i < 8; i++) Max_p(s_in[i], s_out[i], i, p[i]);
}

void InitSbox(int round, int a, int b[9], int c) {
	if (c > 1) {
		if (a != b[c]) InitSbox(round, a, b, c - 1);
	}
	else if (a != b[c]) {
		x[round][a] = 0;
		y[round][a] = 0;
		fr[round][a] = 0;
		mid[round][a] = 0;
		pro[round][a] = 0;
	}
}
double MultiPro(double a[8], int k)
{
	double b = log2(1.0);
	for (int j = 0; j < k; j++) b = b + a[j];
	return b;
}
void TravSbox1_1() {
	for (s[0][1] = 0; s[0][1] < 8; s[0][1]++) {
		for (int k = 0; k < 8; k++) InitSbox(0, k, s[0], 1);
		for (mid[0][s[0][1]] = 1; mid[0][s[0][1]] < 4; mid[0][s[0][1]]++) {	
			x[0][s[0][1]] = SboxInDiff(fr[0], mid[0], s[0][1]);
			Max_p(x[0][s[0][1]], y[0][s[0][1]], s[0][1], pro[0][s[0][1]]);
			X[0] = InvExtend(fr[0], mid[0]);
			if (pro[0][s[0][1]] + B[r - 2] >= B[r - 1]) {
				p[0] = pro[0][s[0][1]];
				Round2();
			}
		}
	}
}

void TravSbox2_1() {
	for (s[1][1] = 0; s[1][1] < 8; s[1][1]++) {
		for (int k = 0; k < 8; k++) InitSbox(1, k, s[1], 1);
		for (mid[1][s[1][1]] = 1; mid[1][s[1][1]] < 4; mid[1][s[1][1]]++) {
			x[1][s[1][1]] = SboxInDiff(fr[1], mid[1], s[1][1]);
			for (y[1][s[1][1]] = 0; y[1][s[1][1]] < 16; y[1][s[1][1]]++) {
				if (P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]] > -6) {
					pro[1][s[1][1]] = P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]];
					if (p[0] + pro[1][s[1][1]] + B[r - 3] >= B[r - 1]) {
						p[1] = pro[1][s[1][1]];
						temp[1] = p[0] + p[1];
						X[1] = InvExtend(fr[1], mid[1]);
						Y[1] = Permute(y[1]);
						X[2] = X[0] ^ Y[1];
						Round3toR(r, 3, temp[1]);
					}
				}
			}
		}
	}
}
void TravSbox2(int round, int num) {
	switch (num)
	{
	case 0:                                       //两个不相邻，且首尾没有相连
		for (mid[round][s[round][1]] = 1; mid[round][s[round][1]] < 4; mid[round][s[round][1]]++) {
			for (mid[round][s[round][2]] = 1; mid[round][s[round][2]] < 4; mid[round][s[round][2]]++) {
				x[round][s[round][1]] = SboxInDiff(fr[round], mid[round], s[round][1]);
				x[round][s[round][2]] = SboxInDiff(fr[round], mid[round], s[round][2]);
				Max_p(x[round][s[round][1]], y[round][s[round][1]], s[round][1], pro[round][s[round][1]]);
				Max_p(x[round][s[round][2]], y[round][s[round][2]], s[round][2], pro[round][s[round][2]]);		
				if (round == 0) {
					if (pro[round][s[round][1]] + pro[round][s[round][2]] + B[r - 2] >= B[r - 1]) {
						p[round] = pro[round][s[round][1]] + pro[round][s[round][2]];
						X[0] = InvExtend(fr[0], mid[0]);
						Round2();
					}
				}
				else {
					if (pro[round][s[round][1]] + pro[round][s[round][2]] + p[0] + B[r - 3] >= B[r - 1]) {
						//遍历输出
						for (y[1][s[1][1]] = 0; y[1][s[1][1]] < 16; y[1][s[1][1]]++) {
							if (P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]] > -6) {
								pro[1][s[1][1]] = P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]];
								if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
									for (y[1][s[1][2]] = 0; y[1][s[1][2]] < 16; y[1][s[1][2]]++) {
										if (P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]] > -6) {
											pro[1][s[1][2]] = P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]];
											if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
												p[1] = pro[1][s[1][1]] + pro[1][s[1][2]];
												temp[1] = p[0] + p[1];
												X[1] = InvExtend(fr[1], mid[1]);
												Y[1] = Permute(y[1]);
												X[2] = X[0] ^ Y[1];
												Round3toR(r, 3, temp[1]);
											}
										}
									}
								}
							}
						}
					}			
				}
			}
		}
		break;

	case 1:                                                  //首尾相连
		for (fr[round][0] = 0; fr[round][0] < 4; fr[round][0]++) {
			for (fr[round][0] == 0 ? mid[round][0] = 1 : mid[round][0] = 0; mid[round][0] < 4; mid[round][0]++) {
				for (fr[round][0] == 0 ? mid[round][7] = 1 : mid[round][7] = 0; mid[round][7] < 4; mid[round][7]++) {
					x[round][s[round][1]] = SboxInDiff(fr[round], mid[round], s[round][1]);
					x[round][s[round][2]] = SboxInDiff(fr[round], mid[round], s[round][2]);
					Max_p(x[round][s[round][1]], y[round][s[round][1]], s[round][1], pro[round][s[round][1]]);
					Max_p(x[round][s[round][2]], y[round][s[round][2]], s[round][2], pro[round][s[round][2]]);			
					if (round == 0) {
						if (pro[round][s[round][1]] + pro[round][s[round][2]] + B[r - 2] >= B[r - 1]) {
							p[round] = pro[round][s[round][1]] + pro[round][s[round][2]];
							X[0] = InvExtend(fr[0], mid[0]);
							Round2();
						}
					}
					else {
						if (pro[round][s[round][1]] + pro[round][s[round][2]] + p[0] + B[r - 3] >= B[r - 1]) {
							//遍历输出
							for (y[1][s[1][1]] = 0; y[1][s[1][1]] < 16; y[1][s[1][1]]++) {
								if (P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]] > -6) {
									pro[1][s[1][1]] = P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]];
									if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
										for (y[1][s[1][2]] = 0; y[1][s[1][2]] < 16; y[1][s[1][2]]++) {
											if (P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]] > -6) {
												pro[1][s[1][2]] = P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]];
												if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
													p[1] = pro[1][s[1][1]] + pro[1][s[1][2]];
													temp[1] = p[0] + p[1];
													X[1] = InvExtend(fr[1], mid[1]);
													Y[1] = Permute(y[1]);
													X[2] = X[0] ^ Y[1];
													Round3toR(r, 3, temp[1]);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		break;

	default:               //相邻
		for (fr[round][s[round][2]] = 0; fr[round][s[round][2]] < 4; fr[round][s[round][2]]++) {
			for (fr[round][s[round][2]] == 0 ? mid[round][s[round][1]] = 1 : mid[round][s[round][1]] = 0; mid[round][s[round][1]] < 4; mid[round][s[round][1]]++) {
				for (fr[round][s[round][2]] == 0 ? mid[round][s[round][2]] = 1 : mid[round][s[round][2]] = 0; mid[round][s[round][2]] < 4; mid[round][s[round][2]]++) {
					x[round][s[round][1]] = SboxInDiff(fr[round], mid[round], s[round][1]);
					x[round][s[round][2]] = SboxInDiff(fr[round], mid[round], s[round][2]);
					Max_p(x[round][s[round][1]], y[round][s[round][1]], s[round][1], pro[round][s[round][1]]);
					Max_p(x[round][s[round][2]], y[round][s[round][2]], s[round][2], pro[round][s[round][2]]);		
					if (round == 0) {
						if (pro[round][s[round][1]] + pro[round][s[round][2]] + B[r - 2] >= B[r - 1]) {
							p[round] = pro[round][s[round][1]] + pro[round][s[round][2]];
							X[0] = InvExtend(fr[0], mid[0]);
							Round2();
						}
					}
					else {
						if (pro[round][s[round][1]] + pro[round][s[round][2]] + p[0] + B[r - 3] >= B[r - 1]) {
							//遍历输出
							for (y[1][s[1][1]] = 0; y[1][s[1][1]] < 16; y[1][s[1][1]]++) {
								if (P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]] > -6) {
									pro[1][s[1][1]] = P[s[1][1]][x[1][s[1][1]]][y[1][s[1][1]]];
									if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
										for (y[1][s[1][2]] = 0; y[1][s[1][2]] < 16; y[1][s[1][2]]++) {
											if (P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]] > -6) {
												pro[1][s[1][2]] = P[s[1][2]][x[1][s[1][2]]][y[1][s[1][2]]];
												if (pro[1][s[1][1]] + pro[1][s[1][2]] + p[0] + B[r - 3] >= B[r - 1]) {
													p[1] = pro[1][s[1][1]] + pro[1][s[1][2]];
													temp[1] = p[0] + p[1];
													X[1] = InvExtend(fr[1], mid[1]);
													Y[1] = Permute(y[1]);
													X[2] = X[0] ^ Y[1];
													Round3toR(r, 3, temp[1]);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		break;
	}
}

void TravSbox3(int a, int j, int round) {
	for (s[round][j] = s[round][j - 1] + 1; s[round][j] < 8 - (a - j); s[round][j]++) {
		if (j < a) TravSbox3(a, j + 1, round);
		else {
			for (int k = 0; k < 8; k++) InitSbox(round, k, s[round], a);
			if (s[round][1] == 0 && s[round][j] == 7) {
				for (fr[round][1] = 0; fr[round][1] < 4; fr[round][1]++) {
					for (mid[round][1] = 0; mid[round][1] < 4; mid[round][1]++) {
						SelectInDiff(fr[round], mid[round], s[round], a, 2, round);
					}
				}
			}
			else {
				fr[round][1] = 0;
				for (mid[round][1] = 0; mid[round][1] < 4; mid[round][1]++) {
					SelectInDiff(fr[round], mid[round], s[round], a, 2, round);
				}
			}
		}
	}
}
void SelectInDiff(ElemType a[8], ElemType b[8], int c[9], int sum, int i, int round) {
	
	if (i <= sum) {
		if (c[i - 1] + 1 == c[i])			//当前s盒与上一个相邻
		{
			for ((a[c[i - 1]] | b[c[i - 1]]) == 0 ? a[c[i]] = 1 : a[c[i]] = 0; a[c[i]] < 4; a[c[i]]++) {
				x[round][c[i - 1]] = SboxInDiff(a, b, c[i - 1]);
				for (b[c[i]] = 0; b[c[i]] < 4; b[c[i]]++) {SelectInDiff(a, b, c, sum, i + 1, round);}
			}
		}
		else {						//不相邻
			a[c[i]] = 0;
			x[round][c[i - 1]] = SboxInDiff(a, b, c[i - 1]);
			if (x[round][c[i - 1]] != 0) {
				for (b[c[i]] = 0; b[c[i]] < 4; b[c[i]]++) { SelectInDiff(a, b, c, sum, i + 1, round); }
			}
		}
	}
	else {
		x[round][c[i - 1]] = SboxInDiff(a, b, c[i - 1]);
		if (x[round][c[i - 1]] != 0) {
			Max_pro(x[round], y[round], pro[round]);
			p[round] = MultiPro(pro[round], 8);
			X[round] = InvExtend(a, b);
			if (round == 0) {
				if (p[0] + B[r - 2] >= B[r - 1]) Round2();
			}
			else {
				if (p[0] + p[1] + B[r - 3] >= B[r - 1]) {				
					Trav_out(1, sum);                       //递归遍历s盒输出，从1到s_num1 
				}
			}
		}
	}
}
ElemType SboxInDiff(ElemType a[8], ElemType b[8], int i) {
	ElemType d;
	d = (a[i] << 4) | (b[i] << 2) | a[(i + 1)%8];
	return d;
}
void BitSplit(u64 a, ElemType b[8]) {
	for (int i = 0; i < 8; i++) b[i] = (a >> (42 - 6 * i))&0x3f;
}
u32 BitMerge(ElemType a[8]) {
	u32 b=0x00000000;
	for (int i = 0; i < 8; i++) b = b^Tr[i][a[i]];
	return b;
}
u32 Permute(ElemType a[8]) {
	u32 b;
	b = p1[a[0]] ^ p2[a[1]] ^ p3[a[2]] ^ p4[a[3]] ^ p5[a[4]] ^ p6[a[5]] ^ p7[a[6]] ^ p8[a[7]];
	return b;
}
u64 Extend(u32 a) {
	u64 b = 0x0000000000000000;
	for (int i = 0; i < 8; i++) b = b^ext[i][(a >> (28 - 4 * i))&0xf];
	return b;
}
//扩展逆变换
u32 InvExtend(ElemType a[8], ElemType b[8]) {
	u32 c = 0x00000000;
	for (int i = 0; i < 8; i++) c = c^FExt[i][a[i]] ^ MExt[i][b[i]];
	return c;
}
//计算下一轮候选概率
double CalCondidatePro(int round) {
	double cp;
	Y[round - 1] = Permute(y[round - 1]);
	X[round] = Y[round - 1] ^ X[round - 2];
	Temp[round] = Extend(X[round]);
	BitSplit(Temp[round], x[round]);
	Max_pro(x[round], y[round], pro[round]);
	p[round] = MultiPro(pro[round], 8);
	cp = B[round - 1] + p[round];
	return cp;
}
#endif // !FUNCTIONS_H_
#pragma once
