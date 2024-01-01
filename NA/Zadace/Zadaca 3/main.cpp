#include <bits/stdc++.h>
#include "AbstractInterpolator.h"
#include "LinearInterpolator.h"
#include "PolynomialInterpolator.h"
#include "PiecewisePolynomialInterpolator.h"
#include "TrigonometricInterpolator.h"
#include "BarycentricInterpolator.h"

int main() {
    /*
    std::vector<std::pair<double, double>> data = {{2.2,1}, {4.5,2}, {1.33,0}, {5.2,3}, {3.7, 2}, {7.9,1}};
    AbstractInterpolator h(data);
    h.printData();
    std::cout<<"Trazeni element (5.2) se nalazi na indeksu: "<<h.Locate(5.2)<<std::endl;
    std::cout<<"Sljedeci trazeni element(7.9) se nalazi na indeksu: "<<h.Locate(7.9)<<std::endl;
    std::cout<<"Sljedeci trazeni element(2.2) se nalazi na indeksu: "<<h.Locate(2.2)<<std::endl;
    std::cout<<"Sljedeci trazeni element(2.3) se nalazi na indeksu: "<<h.Locate(2.3)<<std::endl;
    


    std::vector<std::pair<double, double>> data = 
        {{-4, 0}, {-3.25, -2.25}, {1.5, 2.5}, {4, 0}};
    LinearInterpolator li(data);
    //li.printData();

    std::cout<<li(5);
*/
    std::vector<std::pair<double, double>> data = { {0, 0}, {0.5, 0.5463},
                                                    {-0.5, -0.5463}, 
                                                    {1, 1.5574}, {-1, -1.5574},
                                                    {-0.18, -0.117}, {0.18, 0.117},
                                                    {1.25, 3.01}, {-1.25, -3.01} };
    
    PolynomialInterpolator PI(data);
    //PI.AddPoint({1, 2});
    //PI.AddPoint({-0.16, 0.3333333333333});
    //PI.AddPoint(std::make_pair<double, double>(4, 2.3));
    std::cout << PI(1);
    std::vector<double> koeficijenti = PI.GetCoefficients();    
    std::cout<<"\nKoeficijenti polinoma: \n";
    for(auto a : koeficijenti) {
        std::cout<<a<<" ";
    }
    
    std::cout<<"\n";
    std::cout<<"\n***TRIGONOMETRIC AUTOTEST:***\n";
    //********************************************
    double piTrig = 4*atan(1);
    std::vector<std::pair<double, double>> dataTrig;
    for(double i=0; i<(4.)*piTrig; i+=0.5*piTrig) {
        std::pair<double, double> add = std::make_pair(i, sin(i));
        dataTrig.push_back(add);
    }
    TrigonometricInterpolator ti(dataTrig);
    std::cout<<ti(piTrig/4.);

    //********************************************

    std::cout<<"\n***BARYCENTRIC AUTOTEST:***\n";
    //********************************************

    BarycentricInterpolator bi({{0,8},{1,3},{2,7},{4,5},{7,10}}, 0);
    std::cout << bi(2) << std::endl;
    std::cout << bi(3.5) << std::endl;
    std::cout << bi(7.5) << std::endl;
    std::cout << bi(-3.5);

    //********************************************

    return 0;
}