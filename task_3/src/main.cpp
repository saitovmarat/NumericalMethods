#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>

double a(double i, double h){
    return (1 + i*h);
}
double g(double i, double h){
    return (1 + i*h);
}
double f(double i, double h){
    return -pow(i*h, 6) + 26*pow(i*h, 4) + 4*pow(i*h, 3) - 12*pow(i*h, 2);
}
void printTable(int n, const std::vector<double> y, const std::vector<double> u){
    double h = 1.0 / n; 
    std::cout << std::setw(3) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(8) << " u(ih)"  << " | " << "|yi - u(ih)|" << std::endl;
    for(int i = 0; i < n; i++){
        double ui = u[i];
        double yi = y[i];
        std::cout << std::setw(3) << i*h << " | " << std::setw(12) << yi << " | " 
            << std::setw(8)  << ui << " | " << abs(yi - ui) << std::endl;
    }
}
void SweepMethod_tableOutput(int n){
    double h = 1.0 / n;
    // Counting Alpha and Betta
    std::vector<double> alpha;
    std::vector<double> betta;
    alpha.push_back(0);
    betta.push_back(0);
    for(int i = 1; i < n; i++){
        alpha.push_back(a(i+1,h)/
            ((1 - alpha[i-1]) * a(i, h) + a(i+1, h) + pow(h, 2) * g(i, h))); 
        betta.push_back((f(i, h)*pow(h,2) + betta[i-1] * a(i, h))/
            ((1 - alpha[i-1]) * a(i, h) + a(i+1, h) + pow(h, 2) * g(i, h)));
    }
    // Counting Y
    std::vector<double> y(n);
    y[n] = 0;
    y[n-1] = betta[n-1];
    for(int i = n-1; i > 0; i--){
        y[i-1] = ((a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h)) * y[(n-1)-i] 
        - a(i+1, h) * y[(n-1)-(i+1)] - f(i, h) * pow(h, 2)) / a(i, h);
    }
    // Counting U
    std::vector<double> u(n);
    for(int i = 0; i < n; i++){
        u[i] = pow(i*h, 4) * (1 - (i*h));
    }
    //Printing Table
    std::cout << std::setw(3) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(8) << " u(ih)"  << " | " << "|yi - u(ih)|" << std::endl;
    for(int i = 0; i < n; i++){
        double ui = u[i];
        double yi = y[i];
        std::cout << std::setw(3) << i*h << " | " << std::setw(12) << yi << " | " 
            << std::setw(8)  << ui << " | " << abs(yi - ui) << std::endl;
    }
}



int main(){
    SweepMethod_tableOutput(10);
    return 0;
}
