#include "Function.h"

void Function::set_FuncType(FuncType typeToCopy){
    type = typeToCopy;
}

double Function::Qn(double n, double x){
    return -(((x * x) / (n + 1)) * ((2 * n + 1) / (2 * n + 3)));
}
double Function::erf(double x){
    int n = 1;
    double prevA = x;
    double currentA = x;    
    double result = x;
    while (abs(prevA) >= Eps){
        currentA = Qn(n - 1, x) * prevA;
        result += currentA;
        prevA = currentA;
        n++;
    }
    result *= 2 / sqrt(M_PI);
    return result;
}

float func(float t) { return (2 / sqrt(M_PI)) * pow(std::exp(1.0), -(t * t)); }

double Function::Left_Rect(int n, double x){
    double h = x/n;
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        double xi = a + i*h;
        sum += h * func(xi);
    }
    return sum;
}

double Function::Right_Rect(int n, double x){
    double h = x/n;
    double sum = 0.0;
    for(int i = 1; i <= n; i++){
        double xi = a + i*h;
        sum += h * func(xi);
    }
    return sum;
}

double Function::Central_Rect(int n, double x){
    double h = x/n;
    double sum = 0.0;
    double xi = h/2;
    for(int i = 0; i <= n-1; i++){
        sum += h * func(xi);
        xi+=h;
    }
    return sum;
}

double Function::Trapezoid(int n, double x){
    double h = x/n;
    double sum = 0.0;
    double xi = 0.0;
    for(int i = 0; i <= n-1; i++){
        sum += h*(func(xi) + func(xi+h))/2;
        xi += h;
    }
    return sum;
}

double Function::Simpson(int n, double x){
    double h = x/n;
    double sum = 0.0;
    double xi = 0.0;
    for(int i = 0; i <= n-1; i++){
        sum += (func(xi) + 4 * func(xi + h / 2) + func(xi + h)) * h / 6;
        xi += h;
    }
    return sum;
}

double Function::Gaus(int n, double x){
    double h = x/n;
    double num1 = (1 - 1.0 / sqrt(3)) * h / 2;
    double num2 = (1 + 1.0 / sqrt(3)) * h / 2;
    double sum = 0;
    double xi = 0.0;
    for(int i = 0; i <= n-1; i++){
        sum += (func(xi + num1) + func(xi + num2)) * h/2;
        xi += h;
    }
    return sum;
}

void Function::calculateAndWrite(double x, double y){
    double lastJ = 0;
    double J = 0;
    int n = 1;
    do{
        n *= 2;
        lastJ = J;
        J = calculatedFunction(n, x);
    }
    while (abs(lastJ - J) > Eps && n < 1024);
    double accuracy = abs(J - y);
    std::cout << std::setw(3) << x << " & " << std::setw(9) << y << " & " << std::setw(9) << J << " & " << std::setw(11) << accuracy << " & " << n << std::endl;
}
double Function::calculatedFunction(int n, double x){
    double result = 0.0;
    switch(type){
        case leftRec:{
            result = Left_Rect(n, x);
            break;
        }
        case rightRec:{
            result = Right_Rect(n, x);
            break;
        }
        case centralRect:{
            result = Central_Rect(n, x);
            break;
        }
        case trapezoid:{
            result = Trapezoid(n, x);
            break;
        }
        case simpson:{
            result = Simpson(n, x);
            break;
        }
        case gauss:{
            result = Gaus(n, x);
            break;
        }
    }
    return result;
}
void Function::printTable(){
    double* x = new double[11];
    double* y = new double[11];
    x[0] = 0;
    y[0] = erf(x[0]);
    for (int i = 1; i < 11; i++){
        x[i] = x[i - 1] + H;
        y[i] = erf(x[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Left Rectangle\n" << "\033[0m";
    set_FuncType(leftRec);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Right Rectangle\n" << "\033[0m";
    set_FuncType(rightRec);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Central Rectangle\n" << "\033[0m";
    set_FuncType(centralRect);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Trapezoid\n"<< "\033[0m";
    set_FuncType(trapezoid);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Simpson\n" << "\033[0m";
    set_FuncType(simpson);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
    std::cout << "\033[1m" << "\033[3m" << "Gauss\n" << "\033[0m";
    set_FuncType(gauss);
    for (int i = 1; i < 11; i++){
        calculateAndWrite(x[i], y[i]);
    }
}