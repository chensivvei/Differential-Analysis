#ifndef DIFFRESEACH_H_
#define DIFFRESEACH_H_
#include<stdio.h>
#include<math.h>
#include"variables.h"
#include"functions.h"
void DiffResearch(int i) {
	fp = fopen("差分路径.txt", "w");


	B[0] = log2(14 / 64.0);
	B[1] = log2(14 / 64.0);
	B[2] = log2(49 / 1024.0);
	B[3] = log2(49.0 / 1024) + log2(15.0 / 2048) + log2(49.0 / 1024);			//由三轮差分向下进行一轮得到四轮初始值
	for (r = 4; r <= i; r++) {
		start[r - 1] = time(NULL);

		Round1();
		printf("The best differential probability of the %d round is 2^(%f)\n", r, B[r - 1]);
		fprintf(fp, "The best differential probability of the %d round is 2^(%f)\n", r, B[r - 1]);
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

		end[r - 1] = time(NULL);
		printf("time: %.0f s\n", difftime(end[r - 1], start[r - 1]));
		fprintf(fp, "time: %.0f s\n", difftime(end[r - 1], start[r - 1]));
	
		if(r < i) B[r] = CalCondidatePro(r);
	}
}
#endif // !DIFFRESEACH_H_

