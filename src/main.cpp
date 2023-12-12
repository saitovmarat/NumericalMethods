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
        printResults(F_Array(), L_ArrayCheb(), E_ArrayCheb());
        printf("---------------------------\n");
    }
    return 0;
}
