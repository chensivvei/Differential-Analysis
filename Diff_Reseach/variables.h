#ifndef VARIABLES_H__
#define VARIABLES_H__
#include<stdio.h>
#include<time.h>

typedef unsigned int ElemType;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

u32 X[16], Y[16], Tr[8][16];
u64 Temp[16];

ElemType fr[2][8] = { 0 }, mid[2][8] = { 0 };

//s盒输入差分，x[i][j]表示第i+1轮，第j+1个s盒的输入差分，取值为0-63的整数																																		
ElemType x[16][8];		

//s盒输出差分，y[i][j]表示第i+1轮，第j+1个s盒的输出差分，取值为0-15的整数
ElemType y[16][8];		 

//最佳差分路径的概率，B[i]表示i+1轮最好差分路径的概率
double B[16];

//差分传播概率，p[i]表示第i+1的传播概率
double p[16];

//s盒的差分概率，pro[i][j]表示第i+1轮里，第j+1个s盒的差分概率
double pro[16][8];

//中间变量，temp[i]=p[0]*p[1]*...*p[i]
double temp[16];					

//遍历3-r轮时的中间变量，用来临时保存当前轮的差分传播概率，temp3=pro1*pro2*...*pro8
double temp3;

//输入差分bit形式,只考虑右半部分输入，bit[i][j]表示第i+1轮第j+1比特信息，取值0或1
ElemType bit[16][32];	



//轮数
int r;

//前两轮中用来记录活跃s盒的位置，s[i][j]表示第i+1轮第j+1个活跃s盒的位置，取值为-1-7，s[i][0]=-1
int s[2][9];

/*差分概率分布表，为降低运算，该值是取对数之后的结果，程序中所有概率相乘转化为相加，P[i][j][k]表示第i+1个s盒，
输入差分为j，输出差分为k的概率*/
double P[8][64][16];

//文件指针
FILE *fp;

//计时器，给出计算r轮最优差分路径的时长
clock_t start[16], end[16];
 
#endif