#ifndef DiffResearch_h
#define DiffResearch_h

#include<stdio.h>
#include<math.h>
#include"Variables.h"
#include"Functions.h"

void DiffResearch(int round) {

	fp = fopen("present²î·ÖÂ·¾¶.txt", "w");
	B[0] = log2(4 / 16.0);
	B[1] = log2(4 / 16.0) + log2(4 / 16.0) + log2(4 / 16.0);
	for (r = 2; r <= round; r++) {
		start[r - 1] = time(NULL);

		Round1();
		
		for (int i = 0; i < r; i++) {
			printf("round: %2d, ", i);
			fprintf(fp, "round: %2d, ", i);
			printf("Input: %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x, ", bx[i][15], bx[i][14], bx[i][13], bx[i][12], bx[i][11], bx[i][10], bx[i][9], bx[i][8], bx[i][7], bx[i][6], bx[i][5], bx[i][4], bx[i][3], bx[i][2], bx[i][1], bx[i][0]);
			fprintf(fp, "Input: %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x, ", bx[i][15], bx[i][14], bx[i][13], bx[i][12], bx[i][11], bx[i][10], bx[i][9], bx[i][8], bx[i][7], bx[i][6], bx[i][5], bx[i][4], bx[i][3], bx[i][2], bx[i][1], bx[i][0]);
			printf("Output: %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x, ", by[i][15], by[i][14], by[i][13], by[i][12], by[i][11], by[i][10], by[i][9], by[i][8], by[i][7], by[i][6], by[i][5], by[i][4], by[i][3], by[i][2], by[i][1], by[i][0]);
			fprintf(fp, "Output: %x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x, ", by[i][15], by[i][14], by[i][13], by[i][12], by[i][11], by[i][10], by[i][9], by[i][8], by[i][7], by[i][6], by[i][5], by[i][4], by[i][3], by[i][2], by[i][1], by[i][0]);
			printf("Pro: 2^(%.f)\n", bp[i]);
			fprintf(fp, "Pro: 2^(%.f)\n", bp[i]);
		}
		printf("The best differential probability of the %d round is 2^(%.f)\n", r, B[r - 1]);
		fprintf(fp, "The best differential probability of the %d round is 2^(%.f)\n", r, B[r - 1]);
		
		end[r - 1] = time(NULL);
		printf("time: %.0f s\n", difftime(end[r - 1], start[r - 1]));
		fprintf(fp, "time: %.0f s\n", difftime(end[r - 1], start[r - 1]));
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
		printf("----------------------------------------------------------------------------\n");
		fprintf(fp, "----------------------------------------------------------------------------\n");
		
		if(r<round) B[r] = CalCondidatePro(r);

	}
}

#endif // !DiffResearch_h
#pragma once
