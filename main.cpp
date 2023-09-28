#include <iostream>
#include <math.h> 
#define E 0.000001

double Qn(double n, double x){
    return -(((x * x)/(n+1)) * ((2*n+1)/(2*n+3)));
}
int main(){
    double eps = E;

    double sum[10];
    int sumInd = 0;
    double x = 0;
    while(x <= 2){
        double prevA = x;
        sum[sumInd] += prevA;

        double n = 1;

        std::cout << "x = " << x << "\n" /*<< "Qn = " << Qn(n, x) << "\n"*/;

        while(prevA >= eps){
            std::cout << "При n = " << n << "\n";
            std::cout << "Модуль Q[" << n-1 << "] = " << abs(Qn(n-1, x)) <<"\n";
            std::cout << "\n";

            prevA = abs(Qn(n-1, x) * prevA);
            sum[sumInd] += prevA;
            
            //std::cout << prevA << "\n";
            n++;
        }
        std::cout << "Прошелся по циклу " << n << " раз"<< "\n";
        std::cout << "сумма под индексом " << sumInd << " = " << sum[sumInd] << "\n";
        std::cout << "------------------------------------------"<< "\n"; 
        x += 0.2;
        sumInd++;
    }
    return 0;
}