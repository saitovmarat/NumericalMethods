#include "countF.h"
#include "countL.h"

void printResults(double* F, double* L);

int main(){
    double F[6];
    double L[11];

    countF(F);
    countL(F, L);
    printResults(F, L);
    return 0;
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