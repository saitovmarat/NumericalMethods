#include <stdio.h>
#include <math.h>
#define Eps pow(10, -6)

double max(double* function, size_t size);
double Qn(double n, double x);
double countF(double x);
double* F_Array();
double countL(double x, int nodesCount);
double* L_Array(int nodesCount);
double* E_Array(int nodesCount);

//Узлы Чебышева
double chebNode(double i, int nodesCount);
double countL_Cheb(double x, int nodesCount);
double* L_ArrayCheb(int nodesCount);
double* E_ArrayCheb(int nodesCount);

//Вывод результатов
void menu(bool& cheb);
void printResults(double* F, double* L, double* E);
void printResults(int nodesCount, double* E);