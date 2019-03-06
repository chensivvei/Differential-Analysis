#ifndef DiffTable_h
#define DiffTable_h
#include<stdio.h>
#include<math.h>
#include"Variables.h"
#include"const.h"

//²î·Ö±í
void GetDiffTable() {
	u64 InDiff;
	int t[16][16] = { 0 };
	u64 OutDiff;
	for (InDiff = 0; InDiff < 16; InDiff++) {
		for (u64 i = 0; i < 16; i++) {
			OutDiff = S1[i] ^ S1[i^InDiff];
			t[InDiff][OutDiff]++;
		}
		for (int j = 0; j < 16; j++) {
			if(t[InDiff][j] > 0) P[InDiff][j] = log2(t[InDiff][j] / 16.0);
			else P[InDiff][j] = -4;
		}
	}
}

#endif // 
#pragma once
