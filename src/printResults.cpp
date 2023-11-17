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
    for(int i = 0; i < 11; i++){
        double x = chebNode(i);
        spaces  = abs((i/10) - 2);
        printf("x%d = %.1f%*s| ", i, x, spaces, "");
        if(i%2 == 0){
            printf("L(x) = %.6f | F(x) = %.6f | E(x) = %.6f\n", L[i], F[F_index],  E[i]);
            F_index++;
        }else
            printf("L(x) = %.6f | F(x) = %s | E(x) = %.6f\n", L[i], "--------", E[i]);
    }
    printf("Emax = %.6f\n", max(E, 11));
}
void printResults(int node, double* E){
    int spaces;
    if (node/10 > 0) spaces = 1;
    else spaces = 2;
    printf("Node = %d%*s| Emax = %.10f\n", node, spaces, "", max(E, 11));
}

