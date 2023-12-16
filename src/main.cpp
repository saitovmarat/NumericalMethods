#include "main.h"

int main(){
    bool isCheb = false;
    menu(isCheb);
    if(!isCheb){
        for(int nodesCount = 5; nodesCount < 52; nodesCount++){
            if (nodesCount % 10 == 0)
                continue;
            printResults(nodesCount, E_ArraywithDiffNodes(nodesCount));
        }
        printf("---------------------------\n");
    }
    else{
        for(int nodesCount = 5; nodesCount < 45; nodesCount++){
            if (nodesCount % 10 == 0)
                continue;
            printResults(nodesCount, E_ArrayCheb(nodesCount));
        }
        printf("---------------------------\n");
    }
    return 0;
}
