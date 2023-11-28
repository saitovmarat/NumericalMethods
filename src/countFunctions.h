#include <stdio.h>
#include <math.h>
#define Eps pow(10, -6)

double max(double* function, size_t size);
double Qn(double n, double x);

double countF(double x);
double* F_Array();

double countL(double x, int nodesCount);
double* L_ArrayWithDiffNodes(int nodesCount);

double* E_ArraywithDiffNodes(int nodesCount);

//Узлы Чебышева
double chebNode(double i);
double countL_Cheb(double x);
double* L_ArrayCheb();
double* E_ArrayCheb();