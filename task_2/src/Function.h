#include <math.h>
#include <iostream>
#include <iomanip>

#define Eps pow(10, -6)
#define a 0
#define b 2
#define H 0.2

enum FuncType{
    leftRec, rightRec, centralRect, 
    trapezoid, simpson, gauss
};

class Function{
private:
    FuncType type;
public:
    Function() = default;

    void set_FuncType(FuncType type);

    double Qn(double n, double x);
    double erf(double x);

    double calculatedFunction(int n, double x);
    void calculateAndWrite(double x, double y);
    void printTable();

    double Left_Rect(int n, double x);
    double Right_Rect(int n, double x);
    double Central_Rect(int n, double x);
    double Trapezoid(int n, double x);
    double Simpson(int n, double x);
    double Gaus(int n, double x);
};