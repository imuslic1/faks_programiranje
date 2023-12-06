#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>
using std::cin;
using std::cout;

//#define double
long double PI = 3.141592653589;

double f(double x) {
    return sin(x);
}

double fprim(std::function<double(double x)> f, double x) {
    volatile double h = 1e-4;
    return (f(x-2*h)-8*f(x-h)+8*f(x+h)-f(x+2*h))/(12*h);
}

int main() {
    cout<<std::setprecision(20);
    cout<<PI<<"\n";
    cout<<fprim(f, PI/3)<<"\n";
    cout<<cos(PI/3)<<"\n";
    //cout<<f(PI/2.);
    return 0;
}