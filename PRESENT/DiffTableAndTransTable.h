#ifndef DiffTableAndTransTable_h
#define DiffTableAndTransTable_h
#include<stdio.h>
#include<math.h>
#include"Variables.h"
#include"const.h"

//差分表
void GetDiffTable() {
	ElemType InDiff;
	int t[16][16] = { 0 };
	ElemType OutDiff;
	for (InDiff = 0; InDiff < 16; InDiff++) {
		for (int i = 0; i < 16; i++) {
			OutDiff = S[i] ^ S[i^InDiff];
			t[InDiff][OutDiff]++;
		}
		for (int j = 0; j < 16; j++) {
			if(t[InDiff][j] > 0) P[InDiff][j] = log2(t[InDiff][j] / 16.0);
			else P[InDiff][j] = -4;
		}
	}
}

//比特分段对应表
void GetTransTable() {
	for (int i = 0; i<16; i++) {
		for (int j = 0; j<16; j++) {
			T[i][j] = bitmask[j] >> (60 - 4 * i);
		}
	}
}
#endif // 
#pragma once
