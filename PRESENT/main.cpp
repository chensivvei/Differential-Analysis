#include<stdio.h>
#include"const.h"
#include"DiffTableAndTransTable.h"
#include"DiffResearch.h"

void main() {

	start[0] = time(NULL);

	GetDiffTable();

	GetTransTable();

	DiffResearch(31);

	end[0] = time(NULL);
	printf("This program finally takes %.0f s\n", difftime(end[0], start[0]));
	fprintf(fp, "This program finally takes %.0f s\n", difftime(end[0], start[0]));


}