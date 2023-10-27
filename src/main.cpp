#include "countFunctions.h"
#include "printResults.h"

int main(){
    double* Emax = new double[14];
    int cnt = 0;
    for(int nodesCount = 6; nodesCount < 15; nodesCount++){
        double* F = countFWithDiffNodes();
        double* L = countLWithDiffNodes(nodesCount);
        double* E = countEwithDiffNodes(nodesCount);
        Emax[nodesCount-1] = max(E, 11);
        printResults(nodesCount, E);
        cnt++;
        //printResults(F, L, E);
        delete[] F, L, E;
    }
    printf("max Emax = %f\n", max(Emax, 14));
    return 0;
}
