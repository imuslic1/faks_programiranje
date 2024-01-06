#include <iostream>
#include <iomanip>
#include "ChebyshevApproximation.h"

double fun(double x) {
    return x*x; 
}

int main() {

    ChebyshevApproximation approx(fun, -2, 2, 10);
    auto w = std::setw(40);
    auto l = std::left;
    auto f = std::fixed;
    auto sp = std::setprecision(20);

    double testx = 1;

    std::cout<<w<<l<<f<<sp<<"Vrijednost f-je: "<<fun(testx)<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija f-je: "<<approx(testx)<<std::endl;

    ChebyshevApproximation izvod = approx.derivative();
    std::cout<<w<<l<<f<<sp<<"Vrijednost izvoda f-je u: "<<2*testx<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija izvoda f-je: "<<izvod(testx)<<std::endl;

    ChebyshevApproximation integral = approx.antiderivative();
    std::cout<<w<<l<<f<<sp<<"Vrijednost primitivne f-je: "<<(testx*testx*testx)/3<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija primitivne f-je: "<<integral(testx)<<std::endl;
    //chebyshevljeva radi!!!


    return 0;
}