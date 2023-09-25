#include "count_integral.h"

int main() {
    double a = 0.0; // Нижний предел интегрирования
    double b = 1.0; // Верхний предел интегрирования
    scanf("%lf", &b);
    int n = 1000; // Количество интервалов

    double result = 2/sqrt(M_PI) * trapezoidal_integral(a, b, n);

    printf("Приближенный интеграл: %f\n", result);

    return 0;
}
