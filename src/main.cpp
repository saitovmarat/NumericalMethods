#include "countFunctions.h"
#include "printResults.h"

int main(){
    bool isCheb = false;
    menu(isCheb);
    if(!isCheb){
        for(int nodesCount = 6; nodesCount < 51; nodesCount++){
            if (nodesCount % 10 == 1)
                continue;
            double* E = countEwithDiffNodes(nodesCount);
            printResults(nodesCount, E);
            delete[] E;
        }
        printf("---------------------------\n");
    }
    else{
        double* F = F_ArrayCheb();
        double* L = L_ArrayCheb();
        double* E = E_ArrayCheb();
        printResults(F, L, E);
        delete[] F;
        delete[] L;
        delete[] E;
        printf("---------------------------\n");
    }
    return 0;
}
