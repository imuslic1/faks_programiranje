#include <iostream>
#include <iomanip>
#include "ChebyshevApproximation.h"

double fun(double x) {
    return cos(x); 
}

int main() {
    ChebyshevApproximation approx(fun, 0, 2*PI, 200);
    auto w = std::setw(40);
    auto l = std::left;
    auto f = std::fixed;
    auto sp = std::setprecision(20);

    double testx = PI/4;

    std::cout<<w<<l<<f<<sp<<"Vrijednost f-je u x = 0: "<<fun(testx)<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija f-je u x = 0: "<<approx(testx)<<std::endl;
    


    return 0;
}