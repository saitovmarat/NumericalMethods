#include "main.h"

int main(){
    bool isCheb = false;
    menu(isCheb);
    if(!isCheb){
        for(int nodesCount = 6; nodesCount < 51; nodesCount++){
            if (nodesCount % 10 == 1)
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
