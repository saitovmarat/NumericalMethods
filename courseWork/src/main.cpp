
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <map>
#include <string>
#include <iterator>
#include <cassert>
#include <fstream>

int main() {
    double h = 0.0001;
    double a = -10;
    double b = -5;
    int N = static_cast<int>((b - a) / h);
    std::vector<double> x(N);
    std::iota(x.begin(), x.end(), a);
    std::transform(x.begin(), x.end(), x.begin(), [h](double xi) { return xi * h; });

    auto y1 = [](double x, double y2) { return -y2 / x; };
    auto y2 = [](double x, double y1) { return -y1 / x; };

    std::vector<double> y1Vals(N, 0);
    std::vector<double> y2Vals(N, 0);
    y1Vals[0] = -10.0 / 3;
    y2Vals[0] = 10.0 / 3;

    for (int i = 0; i < N - 1; ++i) {
        double k11 = y1(x[i], y2Vals[i]);
        double k12 = y2(x[i], y1Vals[i]);
        double k21 = y1(x[i] + h / 4, y2Vals[i] + h * k12 / 4);
        double k22 = y2(x[i] + h / 4, y1Vals[i] + h * k11 / 4);
        double k31 = y1(x[i] + h / 2, y2Vals[i] + h * k22 / 2);
        double k32 = y2(x[i] + h / 2, y1Vals[i] + h * k21 / 2);
        double k41 = y1(x[i] + h, y2Vals[i] + h * k12 - 2 * h * k22 + 2 * h * k32);
        double k42 = y2(x[i] + h, y1Vals[i] + h * k11 - 2 * h * k21 + 2 * h * k31);
        y1Vals[i + 1] = y1Vals[i] + h * (k11 + 4 * k31 + k41) / 6;
        y2Vals[i + 1] = y2Vals[i] + h * (k12 + 4 * k32 + k42) / 6;
    }

    // Plotting using a file
    std::ofstream plotFile("plot.dat");
    for (int i = 0; i < N; ++i) {
        plotFile << x[i] << " " << y1Vals[i] << " " << y2Vals[i] << "\n";
    }
    plotFile.close();

    // Error analysis part
    std::vector<double> h_values;
    for (double hi = 0.5; hi >= 0.001; hi -= 0.001) {
        h_values.push_back(hi);
    }
    int L = h_values.size();
    std::vector<double> errors(L, 0);
    int j = 0;

    auto y1_correct = [](double x) { return x / 3; };
    auto y2_correct = [](double x) { return -x / 3; };

    for (double hi : h_values) {
        int Ni = static_cast<int>((b - a) / hi);
        std::vector<double> xi(Ni);
        std::iota(xi.begin(), xi.end(), a);
        std::transform(xi.begin(), xi.end(), xi.begin(), [hi](double xii) { return xii * hi; });

        std::vector<double> y1Vals(Ni, 0);
        std::vector<double> y2Vals(Ni, 0);
        y1Vals[0] = -10.0 / 3;
        y2Vals[0] = 10.0 / 3;

        for (int i = 0; i < Ni - 1; ++i) {
            double k11 = y1(xi[i], y2Vals[i]);
            double k12 = y2(xi[i], y1Vals[i]);
            double k21 = y1(xi[i] + hi / 4, y2Vals[i] + hi * k12 / 4);
            double k22 = y2(xi[i] + hi / 4, y1Vals[i] + hi * k11 / 4);
            double k31 = y1(xi[i] + hi / 2, y2Vals[i] + hi * k22 / 2);
            double k32 = y2(xi[i] + hi / 2, y1Vals[i] + hi * k21 / 2);
            double k41 = y1(xi[i] + hi, y2Vals[i] + hi * k12 - 2 * hi * k22 + 2 * hi * k32);
            double k42 = y2(xi[i] + hi, y1Vals[i] + hi * k11 - 2 * hi * k21 + 2 * hi * k31);
            y1Vals[i + 1] = y1Vals[i] + hi * (k11 + 4 * k31 + k41) / 6;
            y2Vals[i + 1] = y2Vals[i] + hi * (k12 + 4 * k32 + k42) / 6;
        }

        std::vector<double> y1Ans(Ni), y2Ans(Ni);
        std::transform(xi.begin(), xi.end(), y1Ans.begin(), y1_correct);
        std::transform(xi.begin(), xi.end(), y2Ans.begin(), y2_correct);

        double er1 = *std::max_element(y1Vals.begin(), y1Vals.end()) - *std::max_element(y1Ans.begin(), y1Ans.end());
        double er2 = *std::max_element(y2Vals.begin(), y2Vals.end()) - *std::max_element(y2Ans.begin(), y2Ans.end());
        errors[j] = std::max(er1, er2);
        j++;
    }

    std::vector<double> er(L);
    for (int i = 0; i < L; ++i) {
        er[i] = errors[i] / std::pow(h_values[i], 4);
    }

    // Plotting error data using a file
    std::ofstream errorPlotFile("error_plot.dat");
    for (int i = 0; i < L; ++i) {
        errorPlotFile << h_values[i] << " " << er[i] << "\n";
    }
    errorPlotFile.close();
}

