#include "countFunctions.h"

void printResults(double* F, double* L, double* E);

int main(){
    double F[6];
    double L[11];
    double E[11];

    countF(F);
    countL(L);
    countE(E);
    printResults(F, L, E);
    return 0;
}

void printResults(double* F, double* L, double* E){
    int spaces = 0;
    double x = 0.0;
    int F_index = 0;
    for(int i = 0; i < 11; i++){
        spaces  = abs((i/10) - 2);
        printf("x%d = %.1f%*s| ", i, x, spaces, "");
        if(i%2 == 0){
            printf("F(x) = %.6f | L(x) = %.6f | E(x) = %.6f\n",  F[F_index],  L[i],  E[i]);
            F_index++;
        }else
            printf("F(x) = %s | L(x) = %.6f | E(x) = %.6f\n",  "--------",  L[i],  E[i]);
        x += 0.2;
    }
    printf("Emax = %.6f\n", max(E, 11));
    printf("---------------------------------\n");
}