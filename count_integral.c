#include "count_integral.h"

double function(double x) {
    return exp(-pow(x, 2));
}

double trapezoidal_integral(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    int i;

    sum += function(a) + function(b); // Add the first and last terms

    for (i = 1; i < n; i++) {
        double x = a + i * h;
        sum += 2 * function(x); // Add the middle terms (multiplied by 2)
    }

    return sum * h / 2; // Multiply by h/2 to get the approximate integral
}

