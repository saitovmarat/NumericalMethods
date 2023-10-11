#include "countF.h"

double Qn(double n, double x){
    return -(((x * x) / (n + 1)) * ((2 * n + 1) / (2 * n + 3)));
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