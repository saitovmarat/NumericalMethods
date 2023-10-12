#include "countFunctions.h"

double Qn(double n, double x){
    return -(((x * x) / (n + 1)) * ((2 * n + 1) / (2 * n + 3)));
}
double countF(double x){
    double eps = E;
    double result = 0;
    int n = 0;
    
    double prevA = 0;
    double currentA = x;

    result += currentA;
    prevA = currentA;

    n++;
    while (abs(prevA) >= eps)
    {
        currentA = Qn(n - 1, x) * prevA;
        result += currentA;
        prevA = currentA;

        n++;
    }
    result *= 2 / sqrt(M_PI);
    return result;
}
void countF(double *F){
    double eps = E;
    double h = 0.4;

    int sumInd = 0;

    double x = 0;
    while (x <= 2)
    {
        int n = 0;

        double prevA = 0;
        double currentA = x;

        F[sumInd] += currentA;
        prevA = currentA;

        n++;
        while (abs(prevA) >= eps)
        {
            currentA = Qn(n - 1, x) * prevA;
            F[sumInd] += currentA;
            prevA = currentA;

            n++;
        }
        F[sumInd] *= 2 / sqrt(M_PI);

        x += h;
        sumInd++;
    }
}
void countL(double *L){
    int index = 0;
    int n = 6;
    double h = 0.2;
    double x = 0;
    while (x <= 2){
        for (int i = 0; i < n; i++){
            double Fx = countF(x);
            for (int j = 0; j < n; j++){
                if (i == j)
                    continue;
                Fx *= (x - (x + (h * j))) / ((x + (h * i)) - (x + (h * j))); //Problem may be here
            }
            L[index] += Fx;
        }
        index++;
        x += h;
    }
}