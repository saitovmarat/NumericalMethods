#include "main.h"

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
    int n = 1;
    double prevA = x;
    double currentA = x;    
    double result = x;
    while (abs(prevA) >= eps){
        currentA = Qn(n - 1, x) * prevA;
        result += currentA;
        prevA = currentA;
        n++;
    }
    result *= 2 / sqrt(M_PI);
    return result;
}
double* F_Array(){ 
    double* F = new double[11];
    double eps = Eps;
    double h = 0.2;
    int i = 0;
    for(double x = 0; x <= 2; x += h, i++)
        F[i] = countF(x);
    return F;
}
double countL(double x, int nodesCount){
    double result = 0.0;
    double h = 2/((double)nodesCount);
    for (int i = 0; i < nodesCount+1; i++){
        double xi = i*h;
        double Fx = countF(xi);
        for (int j = 0; j < nodesCount+1; j++){
            if (i == j)
                continue;
            double xj = j*h;
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    return result;
}
double* L_ArrayWithDiffNodes(int nodesCount){ 
    double* L = new double[11];
    double h = 0.2;
    for(int i = 0; i < 11; i++){
        double x = i*h;
        L[i] = countL(x, nodesCount+1);
    }    
    return L;
}


double* E_ArraywithDiffNodes(int nodesCount){
    double* E = new double[11];
    double h = 0.2; 
    for(int i = 0; i < 11; i++){
        double x = i*h;
        E[i] = abs(countF(x) - countL(x, nodesCount));
    }    
    return E;
}

//Узлы Чебышева
double chebNode(double i, int nodesCount){
    double b = 2;
    double a = 0;
    double result = (b+a)/2 + ((b-a)/2)*cos(((2*i+1)/(2*nodesCount+1))*M_PI);
    return result;
}
double countL_Cheb(double x, int nodesCount){
    double result = 0.0;
    for (int i = 0; i < nodesCount+1; i++){
        double xi = chebNode(i, nodesCount);
        double Fx = countF(xi);
        for (int j = 0; j < nodesCount+1; j++){
            if (i == j)
                continue;
            double xj = chebNode(j, nodesCount);
            Fx *= (x - xj) / (xi - xj);
        }
        result += Fx;     
    }
    return result;
}
double* L_ArrayCheb(int nodesCount){ 
    double* L = new double[11];
    double x = 0.0;
    for(int i = 0; i < 11; i++){
        L[i] = countL_Cheb(x, nodesCount);
        x+=0.2;
    }  
    return L;
}
double* E_ArrayCheb(int nodesCount){
    double* E = new double[11];
    double* F = F_Array();
    double* L = L_ArrayCheb(nodesCount);
    for(int i = 0; i < 11; i++){
        double F_x = F[i];
        double L_x = L[i];
        E[i] = abs(F_x - L_x);
    }    
    delete[] F;
    delete[] L;
    return E;
}