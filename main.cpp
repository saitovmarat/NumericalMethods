#include <iostream>
#include <math.h>
#define E pow(10, -6)

double Qn(double n, double x);
void printResults(double x, int sumInd, double sumValue);

int main(){
    double eps = E;

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

        printResults(x, sumInd, sum[sumInd]);

        x += 0.2;
        sumInd++;
    }
    return 0;
}

double Qn(double n, double x){
    return -(((x * x)/(n+1)) * ((2*n+1)/(2*n+3)));
}
void printResults(double x, int sumInd, double sumValue){
    std::cout << "x" << sumInd << " = " << x;
    std::cout << "   F(x" << sumInd << ") = " << sumValue << "\n";
}