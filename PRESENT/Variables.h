#ifndef Variables_h
#define Variables_h
#include<stdio.h>
#include<time.h>
#include"const.h"


FILE *fp;

clock_t start[31], end[31];

//轮数
int r;

//转换表
u64 T[16][16];

//s盒差分概率，每轮差分传播概率，每轮最佳差分传播概率最佳差分路径概率
double P[16][16], p[31], bp[31], B[31], temp[31] = {0.0}, pro[31][16];

//输入输出差分
u64 X[31], Y[31];

//s盒输入差分，和最佳差分路径
ElemType x[31][16], y[31][16], bx[31][16], by[31][16];

//活跃s盒
int s[17];


#endif // !Variables_h
#pragma once
