#include "Function.h"

int main(){
    Function func(leftRec);
    double error = 1;
    for(int n = 2; error; n*=2){
        error = func.printTable(n);
    }
    return 0;
}
