#pragma once 

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
std::vector<double> SweepMethod_result(int n){
    double h = 1.0 / n;
    std::vector<double> alpha(n+1);
    std::vector<double> betta(n+1);
    for(int i = 2; i <= n; i++){
        alpha[i] = a(i,h)/
            ((1 - alpha[i-1]) * a(i-1, h) + a(i, h) + pow(h, 2) * g(i-1, h));
        betta[i] = (f(i-1, h)*pow(h,2) + betta[i-1] * a(i-1, h))/
            ((1 - alpha[i-1]) * a(i-1, h) + a(i, h) + pow(h, 2) * g(i-1, h));
    }
    std::vector<double> y(n+1);
    y[n] = 0;
    for(int i = n-1; i > 0; i--){
        y[i] = alpha[i+1] * y[i+1] + betta[i+1];
    }
    return y;
}
void SweepMethod_tableOutput(int n){
    std::cout << "\033[1m" << "\033[3m" << "Sweep Method\n" << "\033[0m";
        std::cout << std::setw(4) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(12) << " ui"  << " | " << std::setw(12) << "|yi - ui|" << std::endl;
    double h = 1.0 / n;

    std::vector<double> y = SweepMethod_result(n);
    for(int i = 1; i < n; i++){
        double ui = pow(i*h, 4) * (1 - (i*h));;
        double yi = y[i];
        std::cout << std::setw(4) << i*h << " | " << std::setw(12) << yi << " | " 
            << std::setw(12) << ui << " | " << std::setw(12) << abs(yi - ui) << std::endl;
    }
    std::cout << "---\n";
}

void JakobiMethod_tableOutput(int n){
    std::cout << "\033[1m" << "\033[3m" << "Jakobi Method\n" << "\033[0m";
    std::cout << std::setw(4) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(12) << " yi_k"  << " | " << std::setw(12) << "|yi - yi_k|" << " | " << "k" << std::endl;
    
    double h = 1.0/n;
    double eps = pow(h, 3);
    std::vector<double> y_k(n);
    for(int i = 1; i < n-1; i++){
        y_k[i] = f(i, h)*pow(h,2) / (a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h));
    }
    double r = 1;
    std::vector<double> y_k_1(n);
    int k_count = 0;
    while(fabs(r) > eps){
        y_k = y_k_1;
        for(int i = 1; i < n; i++){
            y_k_1[i] = (a(i, h)*y_k[i-1] + a(i+1, h)*y_k[i+1] + f(i, h)*pow(h, 2))
                /(a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h));
            if(i == 1) r = fabs((y_k_1[i] - y_k[i]) / y_k_1[i]);
            else r = std::max(fabs((y_k_1[i] - y_k[i]) / y_k_1[i]), r);
        }
        k_count++;
    } 
    std::vector<double> yi = SweepMethod_result(n);
    // Table output
    for(int i = 1; i < n; i++){
        std::cout  << std::setw(4) << i*h << " | " << std::setw(12) << yi[i] << " | " 
            << std::setw(12) << y_k_1[i] << " | " << std::setw(12) << fabs(yi[i] - y_k_1[i]) << " | " << k_count << std::endl;
    }
    std::cout << "---\n";
}

void upperRelaxationMethod_tableOutput(int n){
    std::cout << "\033[1m" << "\033[3m" << "Upper relaxation Method\n" << "\033[0m";
    std::cout << std::setw(4) << "w" << " | " << "k\n";
    double h = 1.0/n;

    int min_k = pow(2, 10);
    double w_min_k = 2e+10;
    std::vector<double> y_k_lowest(n);
    for(double w = 1.0 + h; w < 2; w += 0.1) {
        double h = (1.0/n);
        double eps = pow(h, 3);
        std::vector<double> y_k(n);
        for(int i = 1; i < n-1; i++) {
            y_k[i] = f(i,h)*h*h / (a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h));
        }
        double r = 1;
        int k = 1;
        std::vector<double> y_k_1(n);
        while(fabs(r) > eps) {
            y_k = y_k_1;
            for(int i = 1; i < n-1; i++) {
                double I = (a(i, h)*y_k_1[i-1] + a(i+1, h)*y_k[i+1] + f(i, h)*pow(h, 2))
                     /(a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h));
                y_k_1[i] = (1-w) * y_k[i] + w*I ;
                if(i == 1) r = fabs((y_k_1[i] - y_k[i])/y_k_1[i]);
                else r = std::max(fabs((y_k_1[i] - y_k[i])/y_k_1[i]), r);
            }
            k++;
        }
        if(k < min_k){
            y_k_lowest = y_k_1;
            min_k = k;
            w_min_k = w;  
        }
        std::cout << std::setw(4) << w << " | " << k << std::endl;
    }
    std::vector<double> yi = SweepMethod_result(n);
    std::cout << "w with minimal k = " << w_min_k << "\n";
    std::cout << std::setw(4) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(12) << " yi_k"  << " | " << std::setw(12) << "|yi - yi_k|" << " | " << "k" << std::endl;
    // Table output
    for(int i = 1; i < n; i++){
        std::cout  << std::setw(4) << i*h << " | " << std::setw(12) << yi[i] << " | " 
            << std::setw(12) << y_k_lowest[i] << " | " << std::setw(12) << fabs(yi[i] - y_k_lowest[i]) << " | " << min_k <<  std::endl;
    }
    std::cout << "---\n";
}

void descentMethod_tableOutput(int n){
    std::cout << "\033[1m" << "\033[3m" << "Descent Method\n" << "\033[0m";
    std::cout << std::setw(4) << "i*h" << " | " << std::setw(12) << "yi" << " | " << std::setw(12) << " yi_k"  << " | " << std::setw(12) << "|yi - yi_k|" << " | " << "k" << std::endl;
    double h = 1.0 / n;
    double eps = pow(h, 3);
    std::vector<double> y_k(n);
    for(int i = 1; i < n-1; i++){
        y_k[i] = f(i, h)*pow(h,2) / 
            (a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h));
    }
    double r = 1;
    std::vector<double> r_k(n);
    int k_count = 0;
    while(fabs(r) > eps){
        r = -1000000000;
        for(int i = 1; i < n-1; i++){
            r_k[i] = -a(i, h)*y_k[i-1] + (a(i, h) + a(i+1, h) + pow(h, 2)*g(i, h))*y_k[i] - a(i+1, h)*y_k[i+1] - f(i, h)*pow(h, 2);
            r = std::max(r, r_k[i]);
        }
        std::vector<double> Ar(n);
        for(int i = 1; i < n-1; i++){
            Ar[i] = -a(i, h)*r_k[i-1] + (a(i, h) + a(i+1, h) + pow(h, 2))*r_k[i] - a(i+1, h)*r_k[i+1];
        }
        double tauNumerator = 0;
        double tauDenominator = 0;
        for(int i = 0; i < n; i++){ 
            tauNumerator += pow(r_k[i], 2);
            tauDenominator += Ar[i]*r_k[i];
        }
        double tau = tauNumerator/tauDenominator;
        for(int i = 0; i < n; i++){
            y_k[i] = y_k[i] - tau*r_k[i];
        }
        k_count++;
    }
    std::vector<double> yi = SweepMethod_result(n);
    // Table output
    for(int i = 1; i < n; i++){
        std::cout  << std::setw(4) << i*h << " | " << std::setw(12) << yi[i] << " | " 
            << std::setw(12) << y_k[i] << " | " << std::setw(12) << abs(yi[i] - y_k[i]) << " | " << k_count << std::endl;
    }
    std::cout << "---\n";
}