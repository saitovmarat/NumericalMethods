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
void countF(double *F){
    double eps = Eps;
    double h = 0.4;

    int sumInd = 0;

    double x = 0;
    while (x <= 2){
        F[sumInd] += countF(x);
        x += h;
        sumInd++;
    }
}
double countL(double x){
    double xij[6] = {0, 0.4, 0.8, 1.2, 1.6, 2};
    double result = 0.0;
    for (int i = 0; i < 6; i++){
        double Fx = countF(xij[i]);
        for (int j = 0; j < 6; j++){
            if (i == j)
                continue;
            Fx *= (x - xij[j]) / (xij[i] - xij[j]);
        }
        result += Fx;     
    }
    return result;
}
void countL(double *L){
    double xij[6] = {0, 0.4, 0.8, 1.2, 1.6, 2};
    double x[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2}; 
    int L_index = 0;
    while (L_index < 11){
        L[L_index]+= countL(x[L_index]);
        L_index++;
    }
}
void countE(double *E){
    for(int i = 0; i < 11; i++){
        double x = i*0.2;
        E[i] = abs(countF(x) - countL(x));
    }
}
