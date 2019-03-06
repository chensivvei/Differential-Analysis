#ifndef Permutation_h
#define Permutation_h

#include"Variables.h"

u64 Permute(int round) {
	u64 temp;
	temp = p1[(y[round][15] << 4) ^ y[round][14]] ^ p2[(y[round][13] << 4) ^ y[round][12]] ^ p3[(y[round][11] << 4) ^ y[round][10]] ^ p4[(y[round][9] << 4) ^ y[round][8]];
	temp = temp^p5[(y[round][7] << 4) ^ y[round][6]] ^ p6[(y[round][5] << 4) ^ y[round][4]] ^ p7[(y[round][3] << 4) ^ y[round][2]] ^ p8[(y[round][1] << 4) ^ y[round][0]];
	return temp;
}

#endif // !Permutation_h
#pragma once
