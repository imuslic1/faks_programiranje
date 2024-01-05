#ifndef CHEBYSHEV_APPROXIMATION
#define CHEBYSHEV_APPROXIMATION
#define PI 4*atan(1)

#include <vector>
#include <cmath>
#include <stdexcept>

class ChebyshevApproximation {
    int m, n;
    double xmin, xmax;
    std::vector<double> c;
public:
    template <typename fun_T>
    ChebyshevApproximation(fun_T f, double xmin, double xmax, int n) {
        if(xmin>=xmax || n<1)
            throw std::domain_error("Bad parameters");
        this->c.resize(n+1);
        this->m = this->n = n;
        this->xmin = xmin;
        this->xmax = xmax;
        std::vector<double> w(4*n+4);
        std::vector<double> v(n+1);

        for(int i=0; i<=n+1; ++i)
            w.at(i) = cos(PI*i/(2*n+2));
        for(int i=0; i<=n/2; ++i)
            v.at(i) = f((xmin + xmax + (xmax - xmin) * w.at(2*i+1))/2.);
        for(int i=n/2+1; i<=n; ++i)
            v.at(i) = f((xmin + xmax - (xmax - xmin) * w.at(2*n+1-2*i))/2.);
        for(int k=0; k<=n; ++k) {
            double s = 0;
            for(int i=0; i<=n; ++i) {
                int p = (k*(2*i+1)) % (4*n+4);
                if(p>2*n+2)
                    p = 4*n+4-p;
                if(p>n+1)
                    s -= v[i]*w[2*n+2-p];
                else s += v[i] * w[p];
            }
            c[k] = 2*s/(n+1);
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
    if(m<1 || m>n)
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






#endif