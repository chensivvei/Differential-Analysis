#include<stdio.h>
#include"variables.h"
#include"DiffTableAndTransTable.h"
#include"DiffReseach.h"


void main() {

	start[0] = time(NULL);

	GetDiffTab();
	//GetTransTab();
	DiffResearch(13);

	end[0] = time(NULL);
	printf("This program finally takes %.0f s\n", difftime(end[0], start[0]));
	fprintf(fp, "This program finally takes %.0f s\n", difftime(end[0], start[0]));

}


