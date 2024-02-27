#include <math.h>
#include <iostream>
#include <iomanip>
#define Eps pow(10, -6)


enum FuncType{
    leftRec, rightRec, centerRect, 
    trapezoid, simpson, gaus
};

class Function{
private:
    const int a = 0;
    double b;
    FuncType type;
public:
    Function(FuncType _type);
    void set_b(double x);
    void set_FuncType(FuncType type);
    FuncType get_FuncType();

    double Qn(double n, double x);
    double erf(double x);

    void setFunctionsValue(double* Fn, double* F2n, double* En, double Fxi, int n, double xi);
    int printTable(int n);

    // #1 Методы Левых и Правых прямоугольников
    double Left_Rect(int n, double x);
    double Right_Rect(int n, double x);

    // #2 Метод Центральных прямоугольников
    double Center_Rect(int n, double x);

    // #3 Метод Трапеций
    double Trapezoid(int n, double x);

    // #4 Квадратная формула Симпсона 
    double Simpson(int n, double x);

    // #5 Квадратная формула Гауса
    double Gaus(int n, double x);
};