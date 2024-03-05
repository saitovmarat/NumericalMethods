#include <math.h>
#include <iostream>
#include <iomanip>

#define Eps pow(10, -6)
#define H 0.2

enum FuncType{
    leftRec, rightRec, centralRect, 
    trapezoid, simpson, gauss
};

class Function{
private:
    const int a = 0;
    double b;
    FuncType type;
public:
    Function();
    void set_b(double x);
    void set_FuncType(FuncType type);
    FuncType get_FuncType();

    double Qn(double n, double x);
    double erf(double x);

    double calculatedFunction(int n, double x);
    void calculateAndWrite(double x, double y);
    void printTable();

    // #1 Методы Левых и Правых прямоугольников
    double Left_Rect(int n, double x);
    double Right_Rect(int n, double x);

    // #2 Метод Центральных прямоугольников
    double Central_Rect(int n, double x);

    // #3 Метод Трапеций
    double Trapezoid(int n, double x);

    // #4 Квадратная формула Симпсона 
    double Simpson(int n, double x);

    // #5 Квадратная формула Гауса
    double Gaus(int n, double x);
};