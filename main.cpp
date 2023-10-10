#include <iostream>
#include <iomanip>
#include <math.h>

double Qn(double n, double x){
    return -(((x * x)/(n+1)) * ((2*n+1)/(2*n+3)));
}

int main(){
    double eps = pow(10, -6);

    double sum[10];
    int sumInd = 0;
    
    double x = 0.0;
    while(x <= 2){
        int n = 0;

        double prevA = 0;
        double currentA = x;
        
        sum[sumInd] += currentA;
        prevA = currentA;
        
        n++;

        while(abs(prevA) >= eps){
            currentA = Qn(n-1, x) * prevA;
            sum[sumInd] += currentA;
            prevA = currentA;

            n++;
        }
        sum[sumInd] *= 2/sqrt(M_PI);

        std::cout << "x" << sumInd << " = " << x;
        std::cout << "   F(x" << sumInd << ") = " << sum[sumInd] << "\n";

        x += 0.2;
        sumInd++;
    }
    return 0;
}