#include <iostream>
#include <math.h>

double Qn(double n, double x){
    return -(((x * x)/(n+1)) * ((2*n+1)/(2*n+3)));
}
int main(){
    double eps = pow(10, -6);

    double sum[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int sumInd = 0;
    double x = 0.0;

    while(x <= 2){
        std::cout << "x" << sumInd << " = " << x << "\n\n";
        double n = 0;
        double prevA = x;
        sum[sumInd] += prevA;
        
        std::cout << "n = " << n << "\n";
        std::cout << "an = " << prevA << "\n\n";

        n++;
        

        while(prevA >= eps){
            std::cout << "n = " << n << "\n";
            //std::cout << "Q" << n-1 << " = " << abs(Qn(n-1, x)) <<"\n";
            
            prevA = Qn(n-1, x) * prevA;
            sum[sumInd] += prevA;
            
            std::cout << "an = " << prevA << "\n";
            std::cout << "\n";
            n++;
        }
        sum[sumInd] *= 2/sqrt(M_PI);
        std::cout << "Кол-во итераций - " << n << "\n";
        std::cout << "F(x" << sumInd << ") = " << sum[sumInd] << "\n";
        std::cout << "------------------------------------------"<< "\n"; 
        x += 0.2;
        sumInd++;
    }
    return 0;
}