#include <stdio.h>
#include <math.h>
#define Eps pow(10, -6)

double max(double* function, size_t size);
double Qn(double n, double x);

double countF(double x);
double* countF();

double countL(double x, int nodesCount);
double* countLWithDiffNodes(int nodesCount);

double* countEwithDiffNodes(int nodesCount);

//Узлы Чебышева
double chebNode(double i);
double* F_ArrayCheb();
double countL_Cheb(double x);
double* L_ArrayCheb();
double* E_ArrayCheb();