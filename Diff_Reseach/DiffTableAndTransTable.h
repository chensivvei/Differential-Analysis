#ifndef DIFFTABLEANDTRANSTABLE_H_
#define DIFFTABLEANDTRANSTABLE_H_
#include<stdio.h>
#include<math.h>
#include"const.h"
#include"variables.h"

//s∫–‘ÀÀ„
ElemType s_box(ElemType input, ElemType s[4][16]) {
	int msb, lsb, x, y;
	lsb = input % 2;
	msb = (input / 32) % 2;
	x = lsb + msb * 2;
	y = (input - (lsb + msb * 32)) / 2;
	return s[x][y];
}
//≤Ó∑÷±Ì
void GetDiffTab() {
	ElemType indiff, outdiff, temp;
	int T[8][64][16] = { 0 };
	for (indiff = 0; indiff <= 63; indiff++) {
		for (int j = 0; j <= 63; j++) {
			temp = indiff ^ j;
			outdiff = s_box(j, s1) ^ s_box(temp, s1);
			T[0][indiff][outdiff]++;

			outdiff = s_box(j, s2) ^ s_box(temp, s2);
			T[1][indiff][outdiff]++;

			outdiff = s_box(j, s3) ^ s_box(temp, s3);
			T[2][indiff][outdiff]++;

			outdiff = s_box(j, s4) ^ s_box(temp, s4);
			T[3][indiff][outdiff]++;

			outdiff = s_box(j, s5) ^ s_box(temp, s5);
			T[4][indiff][outdiff]++;

			outdiff = s_box(j, s6) ^ s_box(temp, s6);
			T[5][indiff][outdiff]++;

			outdiff = s_box(j, s7) ^ s_box(temp, s7);
			T[6][indiff][outdiff]++;

			outdiff = s_box(j, s8) ^ s_box(temp, s8);
			T[7][indiff][outdiff]++;
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 16; j++) {
				if (T[i][indiff][j] > 0) P[i][indiff][j] = log2(T[i][indiff][j] / 64.0);
				else P[i][indiff][j] = -6;
				//printf("%.20lf\n", P[i][indiff][j]);
			}
		}
	}
}

void GetTransTab() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 16; j++) Tr[i][j] = Tr1[j] << (4 * i);
	}
}
#endif // !DIFFTABLEANDTRANSTABLE_H_

