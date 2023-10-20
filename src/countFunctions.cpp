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
void countF(double* F){
    double eps = Eps;
    double h = 0.4;
    int sumInd = 0;

    for(double x = 0; x <= 2; x += h){
        F[sumInd] += countF(x);
        sumInd++;
    }
}
double countL(double x){
    double result = 0.0;
    for (int i = 0; i < 6; i++){
        double xi = i*0.4; // *
        double Fx = countF(xi);
        for (int j = 0; j < 6; j++){
            if (i == j)
                continue;
            double xj = j*0.4; // *
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    return result;
}
void countL(double* L){
    for(int i = 0; i < 11; i++){
        double x = i*0.2; // 0.2 - расстояние между точками
        L[i]+= countL(x);
    }
}   
void countE(double* E){
    for(int i = 0; i < 11; i++){
        double x = i*0.2;
        E[i] = abs(countF(x) - countL(x));
    }
}
