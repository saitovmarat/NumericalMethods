#include "countFunctions.h"
#include "printResults.h"

int main(){
    double* F = new double[6]; //Надо будет перенести этот массив в функцию
    double* L = new double[11];
    double* E = new double[11];

    countF(F);
    countL(L);
    countE(E);
    printResults(F, L, E);

    delete[] F, L, E;
    return 0;
}
