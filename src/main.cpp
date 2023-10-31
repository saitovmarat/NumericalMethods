#include "countFunctions.h"
#include "printResults.h"

int main(){
    for(int nodesCount = 6; nodesCount < 50; nodesCount++){
        if (nodesCount % 10 == 0)
            continue;
        double* E = countEwithDiffNodes(nodesCount);
        printResults(nodesCount, E);
        delete[] E;
    }
    printf("---------------------------\n");
    return 0;
}
