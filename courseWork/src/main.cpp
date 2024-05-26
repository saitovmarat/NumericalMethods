#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define a 0.0
#define b 2.0

double y1_test(double t, double y1, double y2) {
    return (y1 / (2 + 2 * t)) - 2 * t * y2;
}

double y2_test(double t, double y1, double y2) {
    return (y2 / (2 + 2 * t)) + 2 * t * y1;
}

void solve_test(double h, double x0, double y0, std::vector<double>& t, std::vector<double>& y1, std::vector<double>& y2) {
    int n = static_cast<int>((b - a) / h + 1);
    t = std::vector<double>(n);
    y1 = std::vector<double>(n);
    y2 = std::vector<double>(n);
    t[0] = double(a);
    y1[0] = x0;
    y2[0] = y0;

    for (int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + h;
        double k11 = y1_test(t[i], y1[i], y2[i]);
        double k12 = y2_test(t[i], y1[i], y2[i]);

        double k21 = y1_test(t[i] + h / 3, y1[i] + h * k11 / 3, y2[i] + h * k12 / 3);
        double k22 = y2_test(t[i] + h / 3, y1[i] + h * k11 / 3, y2[i] + h * k12 / 3);

        double k31 = y1_test(t[i] + 2 * h / 3, y1[i] - h * k11 / 3 + h * k21, y2[i] - h * k12 / 3 + h * k22);
        double k32 = y2_test(t[i] + 2 * h / 3, y1[i] - h * k11 / 3 + h * k21, y2[i] - h * k12 / 3 + h * k22);
        
        double k41 = y1_test(t[i] + h, y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        double k42 = y2_test(t[i] + h, y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        
        y1[i + 1] = y1[i] + h * (k11 + 3.0 * k21 + 3.0 * k31 + k41) / 8.0;
        y2[i + 1] = y2[i] + h * (k12 + 3.0 * k22 + 3.0 * k32 + k42) / 8.0;
    }
}

void exact(double h, std::vector<double>& y1, std::vector<double>& y2) {
    int n = static_cast<int>((b - a) / h + 1);
    y1.resize(n);
    y2.resize(n);
    for (int i = 0; i < n; ++i) {
        double t = a + i * h;
        y1[i] = std::cos(t * t) * std::sqrt(1 + t);
        y2[i] = std::sin(t * t) * std::sqrt(1 + t);
    }
}

int main() {
    double x0 = 1;
    double y0 = 0;
    int n = 100;
    double h = (b - a) / n;

    // Решение методом Рунге-Кутты 4-го порядка
    std::cout << "Метод Рунге-Кутты 4-го порядка" << std::endl;
    std::vector<double> t(n);
    std::vector<double> x(n);
    std::vector<double> y(n);
    solve_test(h, x0, y0, t, x, y);
    for(int i = 0; i < n; ++i) {
        std::cout << t[i] << " " << x[i] << " " << y[i] << std::endl;
    }

    
    // Точное решение
    // std::cout << "Точное решение" << std::endl;
    // std::vector<double> x1, y1;
    // exact(h, x1, y1);
    // for(int i = 0; i < n; ++i) {
    //     std::cout << t[i] << " " << x1[i] << " " << y1[i] << std::endl;
    // }

    return 0;
}

