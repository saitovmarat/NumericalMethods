#include "Function.h"

Function::Function(FuncType _type){
    type = _type;
}
void Function::set_b(double x){
    b = x;
}
void Function::set_FuncType(FuncType typeToCopy){
    type = typeToCopy;
}
FuncType Function::get_FuncType(){
    return type;
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

// #1 Методы Левых, правых прямоугольников
double Function::Left_Rect(int n, double x){
    double h = (b-a)/n;
    double sum = 0.0;
    for(int i = 0; i <= n-1; i++){
        double xi = a + i*h;
        sum += h * erf(xi);
    }
    return sum;
}
double Function::Right_Rect(int n, double x){
    double h = (b-a)/n;
    double sum = 0.0;
    for(int i = 1; i <= n; i++){
        double xi = a + i*h;
        sum += h * erf(xi);
    }
    return sum;
}

// #2 Метод Центральных прямоугольников
double Function::Center_Rect(int n, double x){
    double h = (b-a)/n;
    double sum = 0.0;
    for(int i = 0; i <= n-1; i++){
        double xi_1 = a + i*h;
        double xi_2 = a + (i+1)*h;
        sum += h * ((erf(xi_1) + erf(xi_2))/2);
    }
    return sum;
}

// #3 Метод Трапеций
double Function::Trapezoid(int n, double x){
    double h = (b-a)/n;
    double sum = erf(a) + erf(b);
    for(int i = 1; i <= n-1; i++){
        double xi = a + i*h;
        sum += 2*erf(xi);
    }
    sum *= h/2;
    return sum;
}

// #4 Квадратная формула Симпсона 
double Function::Simpson(int n, double x){
    double h = (b-a)/n;
    double sum = 0;
    for(int i = 0; i <= n-1; i++){
        double xi_1 = a + i*h;
        double xi_2 = a + (i+1)*h;
        sum += erf(xi_1) + 4*erf((xi_1 + xi_2)/2) + erf(xi_2);
    }
    sum *= h/6;
    return sum;
}

// #5 Квадратная формула Гауса
double Function::Gaus(int n, double x){
    double h = (b-a)/n;
    double sum = 0;
    for(int i = 0; i <= n-1; i++){
        double xi_1 = a + i*h;
        double xi_2 = a + (i+1)*h;
        sum += erf(xi_1 + ((xi_2 - xi_1)/2)*(1 - 1/sqrt(3))); 
        sum += erf(xi_1 + ((xi_2 - xi_1)/2)*(1 + 1/sqrt(3)));
    }
    sum *= h/2;
    return sum;
}

void Function::setFunctionsValue(double* Fn, double* F2n, double* En, double Fxi, int n, double xi){
    switch(type){
        case leftRec:{
            *Fn = Left_Rect(n, xi);
            *F2n = Left_Rect(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
        case rightRec:{
            *Fn = Right_Rect(n, xi);
            *F2n = Right_Rect(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
        case centerRect:{
            *Fn = Center_Rect(n, xi);
            *F2n = Center_Rect(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
        case trapezoid:{
            *Fn = Trapezoid(n, xi);
            *F2n = Trapezoid(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
        case simpson:{
            *Fn = Simpson(n, xi);
            *F2n = Simpson(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
        case gaus:{
            *Fn = Gaus(n, xi);
            *F2n = Gaus(2*n, xi);
            *En = abs(*(Fn)-Fxi);
            break;
        }
    }
}

int Function::printTable(int n){
    double minSub = 1;
    int error = 1;
    double h = 0.2;
    double En, Fn, F2n;
    std::cout << "------------------------------------------------------------------------------\n";
    for(int i = 1; i < 11; i++){
        double xi = a + i*h;
        set_b(xi);
        double Fxi = erf(xi);
        setFunctionsValue(&Fn, &F2n, &En, Fxi, n, xi);

        if(abs(F2n-Fn) < minSub)
            minSub = abs(F2n-Fn);

        std::cout << "| xi = " << std::setw(3) << xi;
        std::cout << " | F(xi) = " << std::setw(8) << Fxi; 
        std::cout << " | Fn = " << std::setw(9) << Fn;
        std::cout << " | F2n = " << std::setw(9) << F2n;
        std::cout << " | |F2n-Fn| = " << std::setw(9) << minSub;
        std::cout << " | E = " << std::setw(9) << En;
        std::cout << " | n = " << std::setw(3) << n << " |\n"; 
    }
    std::cout << "------------------------------------------------------------------------------\n";
    if (minSub < Eps)
        error = 0;

    return error;
}

