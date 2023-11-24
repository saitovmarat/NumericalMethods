#include "printResults.h"
#include "countFunctions.h"

void menu(bool& cheb){
    int res;
    printf("Узлы Чебышева?\n1 - Да\n2 - Нет\n");
    scanf("%d", &res);
    if (res == 1) cheb = true;
    else cheb = false; 
}
void printResults(double* F, double* L, double* E){
    int spaces = 0;
    int F_index = 0;
    double x = 0.0;
    for(int i = 0; i < 11; i++){
        spaces  = abs((i/10) - 2);
        printf("x%d = %.1f%*s| ", i, x, spaces, "");
        if(i%2 == 0){
            printf("F(x) = %.6f | L(x) = %.6f | E(x) = %.6f\n", F[F_index], L[i], E[F_index]);
            F_index++;
        }else
            printf("F(x) = %s | L(x) = %.6f | E(x) = %s\n", "--------", L[i], "--------");
        x+=0.2;
    }
    printf("Emax = %.6f\n", max(E, 6));
}
void printResults(int node, double* E){
    int spaces;
    if (node/10 > 0) spaces = 1;
    else spaces = 2;
    printf("nodes = %d%*s| Emax = %.10f\n", node, spaces, "", max(E, 11));
}

