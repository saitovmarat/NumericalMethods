#include "countFunctions.h"

double max(double* function, size_t size){
    double max = -1000;
    for(int i = 0; i < size; i++){
        if (function[i] > max)
            max = function[i];
    }
    return max;
}
double Qn(double n, double x){
    return -(((x * x) / (n + 1)) * ((2 * n + 1) / (2 * n + 3)));
}
double countF(double x){
    double eps = Eps;
    double result = 0;
    int n = 0;

    double prevA = 0;
    double currentA = x;

    result += currentA;
    prevA = currentA;

    n++;
    while (abs(prevA) >= eps){
        currentA = Qn(n - 1, x) * prevA;
        result += currentA;
        prevA = currentA;

        n++;
    }
    result *= 2 / sqrt(M_PI);
    return result;
}
double* countFWithDiffNodes(){ 
    double* F = new double[6];
    double eps = Eps;
    double h = 0.4;
    int sumInd = 0;

    for(double x = 0; x <= 2; x += h){
        F[sumInd] += countF(x);
        sumInd++;
    }
    return F;
}
double countL(double x, int nodesCount){
    double result = 0.0;
    double h = 2/((double)nodesCount-1);
    for (int i = 0; i < nodesCount; i++){
        double xi = i*h;
        double Fx = countF(xi);
        for (int j = 0; j < nodesCount; j++){
            if (i == j)
                continue;
            double xj = j*h;
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    return result;
}
double* countLWithDiffNodes(int nodesCount){ 
    double* L = new double[11];
    double h = 0.2;
    for(int i = 0; i < 11; i++){
        double x = i*h;
        L[i] = countL(x, nodesCount);
    }    
    return L;
}
double* countEwithDiffNodes(int nodesCount){
    double* E = new double[11];
    double h = 0.2; 
    for(int i = 0; i < 11; i++){
        double x = i*h;
        E[i] = abs(countF(x) - countL(x, nodesCount));
    }    
    return E;
}