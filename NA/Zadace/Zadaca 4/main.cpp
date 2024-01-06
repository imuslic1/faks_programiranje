#include <iostream>
#include <iomanip>
#include "ChebyshevApproximation.h"

double fun(double x) {
    return 3*x*x*x*x - 2*x*x*x + 5*x*x - 7*x + 1; 
}

int main() {

    ChebyshevApproximation approx(fun, -1, 1, 10);
    auto w = std::setw(40);
    auto l = std::left;
    auto f = std::fixed;
    auto sp = std::setprecision(20);

    double testx = 0.8;

    std::cout<<w<<l<<f<<sp<<"Vrijednost f-je: "<<fun(testx)<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija f-je: "<<approx(testx)<<std::endl;

    ChebyshevApproximation izvod = approx.derivative();
    double primvalue = 12*testx*testx*testx - 6*testx*testx + 10*testx - 7;
    std::cout<<w<<l<<f<<sp<<"Vrijednost izvoda f-je u: "<<primvalue<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija izvoda f-je: "<<izvod(testx)<<std::endl;

    ChebyshevApproximation integral = approx.antiderivative();
    double intvalue = (3.0 / 5) * testx * testx * testx * testx * testx - 0.5 * testx * testx * testx * testx + (5.0 / 3) * testx * testx * testx - 3.5 * testx * testx + testx;
    std::cout<<w<<l<<f<<sp<<"Vrijednost primitivne f-je: "<<intvalue<<std::endl;
    std::cout<<w<<l<<f<<sp<<"Aproksimacija primitivne f-je: "<<integral(testx)<<std::endl;



    //chebyshevljeva radi!!!


    return 0;
}