#ifndef Functions_h
#define Functions_h
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<math.h>
#include"Variables.h"
#include"DiffTableAndTransTable.h"
#include"Permutation.h"

void Round1();
void TravRound1(int sum, int i);

void Round2toR(int round, double multipro);
void LastRound();
void TravOutDiff(int round, int num);
void BitSplit(u64 a, ElemType *b);
u64 BitMerge(ElemType *a);
void MaxDiffPro(ElemType a, double &b, ElemType &c);
void InitSbox(int a, int *b, int c);
double MultiPro(double *a);
double CalCondidatePro(int round);

//程序执行入口，第一轮
void Round1() {
	double temp_p;
	for (int i = 1; i <= 16; i++) {
		s[0]= -1;
		for (int j = 1; j <= 16; j++) s[j] = 0;
		temp_p = log2(pow(0.25, i));
		if (temp_p + B[r - 2] > B[r - 1]) TravRound1(i, 1);
	}
}
//遍历第一轮,按照活跃s盒个数遍历
void TravRound1(int sum, int i) {
	if (i <= sum) {
		for (s[i] = s[i - 1] + 1; s[i] < 16 - (sum - i); s[i]++) {
			for (int j = 0; j < 16; j++) InitSbox(j, s, i);
			for (x[0][s[i]] = 1; x[0][s[i]] < 16; x[0][s[i]]++) {
				for (y[0][s[i]] = 1; y[0][s[i]] < 16; y[0][s[i]]++) {
					if (P[x[0][s[i]]][y[0][s[i]]] > -4) {
						pro[0][s[i]] = P[x[0][s[i]]][y[0][s[i]]];
						temp[0] = MultiPro(pro[0]);
						if (temp[0] + B[r - 2] > B[r - 1]) TravRound1(sum, i + 1);
					}
				}
			}
		}
	}
	else {
		p[0] = temp[0];
		X[0] = BitMerge(x[0]);
		Round2toR(2, temp[0]);
	}
}

//重新选定活跃s盒时，将不活跃的初始化为0
void InitSbox(int a, int *b, int c) {
	if (c > 1) {
		if (a != b[c]) InitSbox(a, b, c - 1);
	}
	else if (a != b[c]) {
		x[0][a] = 0;
		y[0][a] = 0;
		pro[0][a] = 0;
	}
}
//第二轮至倒数第二轮
void Round2toR(int round, double multipro) {
	if (r > 2) {
		X[round - 1] = Permute(round - 2);
		BitSplit(X[round - 1], x[round - 1]);
		for (int num = 0; num < 16; num++) MaxDiffPro(x[round - 1][num], pro[round - 1][num], y[round - 1][num]);
		p[round - 1] = MultiPro(pro[round - 1]);
		temp[round - 1] = p[round - 1] + multipro;
		if (temp[round - 1] + B[r - round - 1] > B[r - 1]) TravOutDiff(round, 0);
	}
	else LastRound();
}
//遍历输出
void TravOutDiff(int round, int num) {
	if (num <= 15) {
		if (x[round - 1][num] == 0) TravOutDiff(round, num + 1);
		else {
			for (y[round - 1][num] = 1; y[round - 1][num] < 16; y[round - 1][num]++) {
				if (P[x[round - 1][num]][y[round - 1][num]] > -4) {
					pro[round - 1][num] = P[x[round - 1][num]][y[round - 1][num]];
					p[round - 1] = MultiPro(pro[round - 1]);
					if (p[round - 1] + temp[round - 2] + B[r - round - 1] > B[r - 1]) TravOutDiff(round, num + 1);
				}
			}
		}
	}
	else {                                            //16个s盒输出都已遍历，求当前轮的概率
		p[round - 1] = MultiPro(pro[round - 1]);
		if (p[round - 1] + temp[round - 2] + B[r - round - 1] > B[r - 1]) {
			temp[round - 1] = p[round - 1] + temp[round - 2];
			if (round < r - 1) Round2toR(round + 1, temp[round - 1]);
			else LastRound();
		}
	}
}
//最后一轮
void LastRound() {
	X[r - 1] = Permute(r - 2);
	BitSplit(X[r - 1], x[r - 1]);
	for (int num = 0; num < 16; num++) MaxDiffPro(x[r - 1][num], pro[r - 1][num], y[r - 1][num]);
	p[r - 1] = MultiPro(pro[r - 1]);
	if (p[r - 1] + temp[r - 2] > B[r - 1]) {
		B[r - 1] = p[r - 1] + temp[r - 2];
		for (int i = 0; i < r; i++) {
			
			for (int j = 0; j < 16; j++) {
				bx[i][j] = x[i][j];
				by[i][j] = y[i][j];			
			}
			bp[i] = p[i];
			
			/*
			printf("x%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, bx[i][0], bx[i][1], bx[i][2], bx[i][3], bx[i][4], bx[i][5], bx[i][6], bx[i][7], bx[i][8], bx[i][9], bx[i][10], bx[i][11], bx[i][12], bx[i][13], bx[i][14], bx[i][15]);
			fprintf(fp, "x%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, bx[i][0], bx[i][1], bx[i][2], bx[i][3], bx[i][4], bx[i][5], bx[i][6], bx[i][7], bx[i][8], bx[i][9], bx[i][10], bx[i][11], bx[i][12], bx[i][13], bx[i][14], bx[i][15]);
			printf("y%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, by[i][0], by[i][1], by[i][2], by[i][3], by[i][4], by[i][5], by[i][6], by[i][7], by[i][8], by[i][9], by[i][10], by[i][11], by[i][12], by[i][13], by[i][14], by[i][15]);
			fprintf(fp, "y%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, by[i][0], by[i][1], by[i][2], by[i][3], by[i][4], by[i][5], by[i][6], by[i][7], by[i][8], by[i][9], by[i][10], by[i][11], by[i][12], by[i][13], by[i][14], by[i][15]);
			printf("p%d = %.20lf\n", i, pow(2, bp[i]));
			fprintf(fp, "p%d = %.20lf\n", i, pow(2, bp[i]));
			
			printf("x%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, x[i][15], x[i][14], x[i][13], x[i][12], x[i][11], x[i][10], x[i][9], x[i][8], x[i][7], x[i][6], x[i][5], x[i][4], x[i][3], x[i][2], x[i][1], x[i][0]);
			fprintf(fp, "x%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, x[i][15], x[i][14], x[i][13], x[i][12], x[i][11], x[i][10], x[i][9], x[i][8], x[i][7], x[i][6], x[i][5], x[i][4], x[i][3], x[i][2], x[i][1], x[i][0]);
			printf("y%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, y[i][15], y[i][14], y[i][13], y[i][12], y[i][11], y[i][10], y[i][9], y[i][8], y[i][7], y[i][6], y[i][5], y[i][4], y[i][3], y[i][2], y[i][1], y[i][0]);
			fprintf(fp, "y%d = %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d, ", i, y[i][15], y[i][14], y[i][13], y[i][12], y[i][11], y[i][10], y[i][9], y[i][8], y[i][7], y[i][6], y[i][5], y[i][4], y[i][3], y[i][2], y[i][1], y[i][0]);
			printf("p%d = %.20lf\n", i, pow(2, p[i]));
			fprintf(fp, "p%d = %.20lf\n", i, pow(2, p[i]));*/
		}
		/*
		printf("The best differential characteristic probability is 2^(%f) \n", B[r - 1]);
		fprintf(fp, "The best differential characteristic probability is 2^(%f) \n", B[r - 1]);
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
       */
	}
}
//比特切片
void BitSplit(u64 a, ElemType *b) {
	for (int i = 0; i < 16; i++) b[i] = (a >> (4 * i)) & 0xf;
}
//比特合并
u64 BitMerge(ElemType *a) {
	u64 b=0x0000000000000000;
	for (int i = 0; i < 16; i++) b = b^T[i][a[i]];
	return b;
}
//已知s盒输入差分求最大差分概率
void MaxDiffPro(ElemType a, double &b, ElemType &c) {
	double maxpro = -4;
	ElemType maxout;
	for (ElemType i = 0; i < 16; i++) {
		if (maxpro <= P[a][i])
		{
			maxpro = P[a][i];
			maxout = i;
		}
	}
	c = maxout;
	b = maxpro;
}
//概率乘积
double MultiPro(double *a) {
	double b = 0;
	for (int i = 0; i < 16; i++) b = b + a[i];
	return b;
}
//计算某轮的初始候选概率
double CalCondidatePro(int round) {
	Y[round - 1] = BitMerge(y[round - 1]);
	X[round] = Permute(round - 1);
	BitSplit(X[round], x[round]);
	for (int i = 0; i < 16; i++) MaxDiffPro(x[round][i], pro[round][i], y[round][i]);
	return MultiPro(pro[round]) + B[round - 1];
}
#endif // !Functions_h
#pragma once
