#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

#define a 0.0
#define b 20.0
#define sigma 1.0

double y1_test(double t, double y1, double y2) {
    return (y1 / (2 + 2 * t)) - 2 * t * y2;
}

double y2_test(double t, double y1, double y2) {
    return (y2 / (2 + 2 * t)) + 2 * t * y1;
}

double y1_dynamic(double y1, double y2) {
    return y1 - y1*y2;    
}

double y2_dynamic(double y1, double y2) {
    return -sigma*y2 + y1*y2;
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

        double k21 = y1_test(t[i] + h / 3.0, y1[i] + h * k11 / 3, y2[i] + h * k12 / 3.0);
        double k22 = y2_test(t[i] + h / 3.0, y1[i] + h * k11 / 3, y2[i] + h * k12 / 3.0);

        double k31 = y1_test(t[i] + 2.0 * h / 3.0, y1[i] - h * k11 / 3.0 + h * k21, y2[i] - h * k12 / 3.0 + h * k22);
        double k32 = y2_test(t[i] + 2.0 * h / 3.0, y1[i] - h * k11 / 3.0 + h * k21, y2[i] - h * k12 / 3.0 + h * k22);
        
        double k41 = y1_test(t[i] + h, y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        double k42 = y2_test(t[i] + h, y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        
        y1[i + 1] = y1[i] + h * (k11 + 3.0 * k21 + 3.0 * k31 + k41) / 8.0;
        y2[i + 1] = y2[i] + h * (k12 + 3.0 * k22 + 3.0 * k32 + k42) / 8.0;
    }
}

void solve_dynamic(double h, double x0, double y0, std::vector<double>& t, std::vector<double>& y1, std::vector<double>& y2) {
    int n = static_cast<int>((b - a) / h + 1);
    t = std::vector<double>(n);
    y1 = std::vector<double>(n);
    y2 = std::vector<double>(n);
    t[0] = double(a);
    y1[0] = x0;
    y2[0] = y0;

    for (int i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + h;
        double k11 = y1_dynamic(y1[i], y2[i]);
        double k12 = y2_dynamic(y1[i], y2[i]);

        double k21 = y1_dynamic(y1[i] + h * k11 / 3, y2[i] + h * k12 / 3);
        double k22 = y2_dynamic(y1[i] + h * k11 / 3, y2[i] + h * k12 / 3);

        double k31 = y1_dynamic(y1[i] - h * k11 / 3 + h * k21, y2[i] - h * k12 / 3 + h * k22); 
        double k32 = y2_dynamic(y1[i] - h * k11 / 3 + h * k21, y2[i] - h * k12 / 3 + h * k22);
        
        double k41 = y1_dynamic(y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        double k42 = y2_dynamic(y1[i] + h * (k11 - k21 + k31), y2[i] + h * (k12 - k22 + k32));
        
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

int main(){
    double x0 = 3;
    double y0 = 1;
    int n = 100;
    double h = (b - a) / n;
    std::vector<double> t;
    std::vector<double> y1;
    std::vector<double> y2;
    solve_dynamic(h, x0, y0, t, y1, y2);
    std::ofstream f("data.txt");
    for(int i = 0; i < t.size(); ++i) {
        f << y1[i] << " " << y2[i] << "\n";
    }
    f.close();

    return 0;
}

