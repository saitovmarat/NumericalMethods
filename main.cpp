#include <stdio.h>
#include <math.h>
#define E pow(10, -6)

double Qn(double n, double x);
void countF(double *F);
void countL(double *F, double *L);
void printResults(double* F, double* L);

int main(){
    double F[6];
    double L[11];

    countF(F);
    countL(F, L);
    printResults(F, L);
    return 0;
}

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
        // printResults(x, index, L[index], 'L');

        index++;
        x += h;
    }
}
void printResults(double* F, double* L){
    int spaces;
    double x = 0;
    //F
    for(int i = 0; i < 6; i++){
        spaces  = abs((i/10) - 2);
        printf("x%d = %.1F%*s| ", i, x, spaces, "");
        printf("F(x%d) = %.6F\n", i, F[i]);
        x += 0.4;
    }
    printf("---------------------------------\n");
    x = 0;
    //L
    for(int i = 0; i < 11; i++){
        spaces  = abs((i/10) - 2);
        printf("x%d = %.1F%*s| ", i, x, spaces, "");
        printf("L(x%d) = %.6F\n", i, L[i]);
        x += 0.2;
    }
}