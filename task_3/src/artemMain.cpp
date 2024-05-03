#include <math.h>
#include <iostream>
#include <map>
#include <bits/stdc++.h>

using ll = long long;
using namespace std;

const double pi = 3.14159265358979323846;

void PrintTable(int n, vector<double>& y_i, vector<double>& u_i) {
  cout << setw(12) << "ih\t\t" << setw(15) << "y_i\t\t" << setw(15) << "u(ih)\t\t" << "|y_i - u(ih)|\n";
  double h = (1.0/n);
  for(int i = 0; i < n; i++) {
    cout << setw(10) << i*h << "\t\t" << setw(15) << y_i[i] << "\t\t" << setw(15) << u_i[i] << "\t\t" << fabs(y_i[i]-u_i[i]) << "\n";
  } 
  cout << "\n";
}


double func(double x) {
  return (-2)*x + 18*pow(x, 2) - 19 * pow(x, 3) - 6 * pow(x, 4) + 35 * pow(x, 5) - 34 * pow(x, 6); 
}
double a_i(double x) {
  return 1 + pow(x, 3);
}
double b_i(double i, double h) {
  return a_i(i*h) + a_i((i+1)*h) + h*h*(1+(i*h));
}

void TridiagonalMethod(double n) {
  double h = (1.0/n);

  double alpha = -a_i(0) / b_i(0, h);
  double beta = -func(0) / b_i(0, h);

  vector<double> k_alpha;
  k_alpha.push_back(alpha);
  vector<double> k_beta;
  k_beta.push_back(beta);

  for(int i = 1; i < n; i++) {
    k_alpha.push_back(-a_i((i-1)*h)/(b_i((i-1), h) - k_alpha[i-1]*-a_i((i-1)*h)));
    k_beta.push_back((k_beta[i-1]*-a_i((i-1)*h) - func((i-1)*h)) / (b_i((i-1), h) - k_alpha[i-1] * -a_i((i-1)*h)));
  }
  vector<double> y_i(n);
  y_i[n-1] = k_beta[n-1];
  for(int i = n-2; i >= 0; i--) {
    y_i[i] = k_alpha[i]*y_i[i+1] + k_beta[i];
  }
  vector<double> u_i(n);
  for(int i = 0; i < n; i++) {
    u_i[i] = pow(i*h, 3) * pow(1-i*h, 2);
  }
  PrintTable(n, y_i, u_i);
}

void IakobiMethod(int n) {
  double h = (1.0/n);
  double e = pow(h, 3);
  vector<double> y_i(n);
  vector<double> u_i(n);
  for(int i = 1; i < n-1; i++) {
    y_i[i] = func(i*h)*h*h / b_i(i, h);
  }
  double r = 1;
  int approuch = 1;
  vector<double> y_i1(n);
  while(fabs(r) > e) {
    y_i = y_i1;
    for(int i = 1; i < n-1; i++) {
      double current_el = (a_i(i*h)/(b_i(i, h)))*y_i[i-1] + (a_i((i+1)*h)/b_i(i, h))*y_i[i+1] + (func(i*h)*h*h / (b_i(i, h)));
      y_i1[i] = current_el;
      u_i[i] = pow(i*h, 3) * pow((1-i*h), 2);
      if(i == 1) r = fabs((y_i1[i] - y_i[i])/y_i1[i]);
      else r = max(fabs((y_i1[i] - y_i[i])/y_i1[i]), r);
    }
    for(int i = 0; i < n; i++) {
      u_i[i] = pow(i*h, 3) * pow((1-i*h), 2);
    }
    approuch++;
  }
  PrintTable(n, y_i1, u_i);
}

void MethodRelaxation(int n) {
  double w = (1.0/n);
  double w1 = w;
  for(; w <= 1; w += w1) {
    double h = (1.0/n);
  double e = pow(h, 3);
  vector<double> y_i(n);
  vector<double> u_i(n);
  for(int i = 1; i < n-1; i++) {
    y_i[i] = func(i*h)*h*h / b_i(i, h);
  }
  double r = 1;
  int approuch = 1;
  vector<double> y_i1(n);
  while(fabs(r) > e) {
    y_i = y_i1;
    for(int i = 1; i < n-1; i++) {
      double current_el = (a_i(i*h)/(b_i(i, h)))*y_i[i-1] + (a_i((i+1)*h)/b_i(i, h))*y_i[i+1] + (func(i*h)*h*h / (b_i(i, h)));
      y_i1[i] = w * current_el + (1-w) * y_i[i];
      u_i[i] = pow(i*h, 3) * pow((1-i*h), 2);
      if(i == 1) r = fabs((y_i1[i] - y_i[i])/y_i1[i]);
      else r = max(fabs((y_i1[i] - y_i[i])/y_i1[i]), r);
    }
    for(int i = 0; i < n; i++) {
      u_i[i] = pow(i*h, 3) * pow((1-i*h), 2);
    }
    approuch++;
  }
  cout << w << "\t\t" << approuch << "\n";
  }
}



int main() {
  cout.precision(10);
  int n = 10;
  //int n2 = 20;
  TridiagonalMethod(n);
  //IakobiMethod(n);
  //MethodRelaxation(n);
}
// ошибка в методе прогонки изменить 
// сравнивать метод якоби с методом прогонки