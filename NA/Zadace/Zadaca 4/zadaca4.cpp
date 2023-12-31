#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#define PI 4*atan(1)

class ChebyshevApproximation {
    int m;
    double xmin, xmax;
    std::vector<double> c;
    ChebyshevApproximation(std::vector<double> c, double xmin, double xmax)
        : xmin(xmin), xmax(xmax), m(c.size()-1) { this->c = c; }
public:
    template <typename fun_T>
    ChebyshevApproximation(fun_T f, double xmin, double xmax, int m) {
        if(xmin>=xmax || m<1)
            throw std::domain_error("Bad parameters");
        this->c.resize(m+1);
        this->m = m;
        this->xmin = xmin;
        this->xmax = xmax;
        std::vector<double> w(4*m+4);
        std::vector<double> v(m+1);

        for(int i=0; i<=m+1; ++i)
            w.at(i) = cos(PI*i/(2*m+2));
        for(int i=0; i<=m/2; ++i)
            v.at(i) = f((xmin + xmax + (xmax - xmin) * w.at(2*i+1))/2.);
        for(int i=m/2+1; i<=m; ++i)
            v.at(i) = f((xmin + xmax - (xmax - xmin) * w.at(2*m+1-2*i))/2.);
        for(int k=0; k<=m; ++k) {
            double s = 0;
            for(int i=0; i<=m; ++i) {
                int p = (k*(2*i+1)) % (4*m+4);
                if(p>2*m+2)
                    p = 4*m+4-p;
                if(p>m+1)
                    s -= v[i]*w[2*m+2-p];
                else s += v[i] * w[p];
            }
            c[k] = 2*s/(m+1);
        }
    }

    void set_m(int m);
    void trunc(double eps);
    double operator()(double x) const;
    double derivative(double x) const;
    ChebyshevApproximation derivative() const;
    ChebyshevApproximation antiderivative() const;
    double integrate(double a, double b) const;
    double integrate() const;
};

inline void ChebyshevApproximation::set_m(int m) { 
    if(m<=1 || m>this->m)
        throw std::domain_error("Bad order"); 
    this->m = m; 
}

inline void ChebyshevApproximation::trunc(double eps) {
    if(eps<0) throw std::domain_error("Bad tolerance");

    while(m>1 && std::abs(c[m]) < eps) --m;

    if(m == 1 && std::abs(c[0]) < eps)
        throw std::domain_error("Bad tolerance");
}

double ChebyshevApproximation::operator()(double x) const {
    if(x<xmin || x>xmax)
        throw std::domain_error("Bad argument");
    //potencijalno long double zbog real aritmetika shenanigans
    double t = (2 * x - xmin - xmax) / (xmax - xmin);
    double p = 1;
    double q = t;
    double s = c[0]/2 + c[1]*t;
    
    for(int k=2; k<=m; ++k) {
        double r = 2*t*q - p;
        s += c[k] * r;
        p = q;
        q = r;
    }
    return s;
}

double ChebyshevApproximation::derivative(double x) const {
    if(x<xmin || x>xmax)
        throw std::domain_error("Bad argument");
    double t = (2 * x - xmin - xmax) / (xmax - xmin);
        double p = 1;
        double q = 4 * t;
        double s = c[1] + c[2]*q;

        for (int k=3; k<=m; ++k) {
            double r = k*(2*t*q / (k-1) - p/(k-2));
            s += c[k] * r;
            p = q;
            q = r;
        }

        return 2*s / (xmax-xmin);
}

ChebyshevApproximation ChebyshevApproximation::derivative() const {
    std::vector<double> cprim(this->m+1);
    double mi = 4./(xmax - xmin);
    cprim[m] = 0;
    cprim[m-1] = mi * m * c[m];
    cprim[m-2] = mi * (m-1) * c[m-1];

    for(int k = m-3; k>=0; --k) {
        cprim[k] = cprim[k+2] + mi*(k+1)*c[k+1];
    }
    ChebyshevApproximation to_return(cprim, xmin, xmax);   

    return to_return;
}

ChebyshevApproximation ChebyshevApproximation::antiderivative() const {
    std::vector<double> cint(this->m+2); //cint[0] = 0
    double mi = (xmax-xmin) / 4;
    
    for(int k=1; k<=m-1; ++k) {
        cint[k] = mi*(c[k-1]-c[k+1])/k;
    }
    cint[0] = 0;
    cint[m] = mi * c[m-1]/m;
    cint[m+1] = mi * (c[m]/(m+1));        //k=m+1 => m=k-1

    ChebyshevApproximation to_return(cint, xmin, xmax); 
    return to_return;
}

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

    approx.set_m(11);
    

    //chebyshevljeva radi!!!

    return 0;
}