#include "countFunctions.h"

double max(double* function, size_t size){
    double max = -1000;
    for(int i = 0; i < size; i++){
        if (function[i] > max)
            max = function[i];
    }
    return max;
}
double Qn(double n, double x){
    return -(((x * x) / (n + 1)) * ((2 * n + 1) / (2 * n + 3)));
}

double countF(double x){
    double eps = Eps;
    double result = 0;
    int n = 0;

    double prevA = 0;
    double currentA = x;

    result += currentA;
    prevA = currentA;

    n++;
    while (abs(prevA) >= eps){
        currentA = Qn(n - 1, x) * prevA;
        result += currentA;
        prevA = currentA;

        n++;
    }
    result *= 2 / sqrt(M_PI);
    return result;
}
double* countF(){ 
    double* F = new double[6];
    double eps = Eps;
    double h = 0.4;
    int sumInd = 0;

    for(double x = 0; x <= 2; x += h){
        F[sumInd] += countF(x);
        sumInd++;
    }
    return F;
}
double countL(double x, int nodesCount){
    double result = 0.0;
    double h = 2/((double)nodesCount-1);
    for (int i = 0; i < nodesCount; i++){
        double xi = i*h;
        double Fx = countF(xi);
        for (int j = 0; j < nodesCount; j++){
            if (i == j)
                continue;
            double xj = j*h;
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    return result;
}
double* countLWithDiffNodes(int nodesCount){ 
    double* L = new double[11];
    double h = 0.2;
    for(int i = 0; i < 11; i++){
        double x = i*h;
        L[i] = countL(x, nodesCount);
    }    
    return L;
}


double* countEwithDiffNodes(int nodesCount){
    double* E = new double[11];
    double h = 0.2; 
    for(int i = 0; i < 11; i++){
        double x = i*h;
        E[i] = abs(countF(x) - countL(x, nodesCount));
    }    
    return E;
}

//Узлы Чебышева
double chebNode(double i){ // Возвращает значение узла в узле с номером i
    double nodesCnt = 5;
    double b = 2;
    double a = 0;
    double result = (b+a)/2 + ((b-a)/2)*cos(((2*i+1)/(2*nodesCnt+2))*M_PI);
    return result;
}
double* nodes_ArrayCheb(){ // Возвращает массив длинной 6 из узлов
    double* result = new double[6];
    for(int i = 0; i < 6; i++)
        result[i] = chebNode(i);
    return result;
}
double* F_ArrayCheb(){ 
    double* F = new double[6];
    double eps = Eps;
    int sumInd = 0;
    double* nodes = nodes_ArrayCheb();

    for(int i = 0; i < 6; i++){
        F[sumInd] += countF(nodes[i]);
        sumInd++;
    }
    delete[] nodes;
    return F;
}
double countL_Cheb(double x){
    double result = 0.0;
    double* nodes = nodes_ArrayCheb();
    for (int i = 0; i < 6; i++){
        double xi = nodes[i];
        double Fx = countF(xi);
        for (int j = 0; j < 6; j++){
            if (i == j)
                continue;
            double xj = nodes[j];
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    delete[] nodes;
    return result;
}
double* L_ArrayCheb(){ 
    double* L = new double[11];
    double* nodes = nodes_ArrayCheb();
    for(int i = 0; i < 11; i++){
        double x = nodes[i];
        L[i] = countL_Cheb(x);
    }   
    delete[] nodes; 
    return L;
}


double* E_ArrayCheb(){
    double* E = new double[11];
    double* nodes = nodes_ArrayCheb();
    for(int i = 0; i < 11; i++){
        double x = nodes[i];
        E[i] = abs(countF(x) - countL_Cheb(nodes[i]));
    }    
    return E;
}