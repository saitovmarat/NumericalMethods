#include "countL.h"

void countL(double *F, double *L){
    int index = 0;
    int n = 6;
    double h = 0.2;

    double x = 0;
    while (x <= 2)
    {
        for (int i = 0; i < n; i++)
        {
            double Fx = F[i];
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                Fx *= (x - (x + (h * j)) / (x + (h * i) - x + (h * j)));
            }
            L[index] += Fx;
        }
        index++;
        x += h;
    }
}