#ifndef CHEBYSHEV_APPROXIMATION
#define CHEBYSHEV_APPROXIMATION

#include <bits/stdc++.h>
#define PI 4*atan(1);

class ChebyshevApproximation {
    int m, n;
    double xmin, xmax;
    std::vector<double> c;
public:
    template <typename fun_T>
    ChebyshevApproximation(fun_T f, double xmin, double xmax, int n) {
        if(xmin>=xmax || n<1)
            throw std::domain_error("Bad parameters");
        this->m = this->n = n;
        std::vector<double> w(n);
        std::vector<double> v(n);

        for(int i=0; i<=n; ++i)
            w[i] = cos(i*PI/(2*n+2));
        for(int i=0; i<=floor(n/2); ++i)
            v[i] = f((xmin + xmax + (xmax - xmin) * w.at(2*i+1))/2);
        for(int i=floor(n/2)+1; i<=n; ++i)
            v[i] = f((xmin + xmax - (xmax - xmin) * w.at(2*n+1-2*i))/2);
        for(int k=0; k<=n; ++k) {
            double s = 0;
            for(int i=0; i<=n; ++i) {
                short p = k*(2*i+1) % 4*n+4;
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

    while(m>1 && abs(c[m]) < eps) --m;

    if(m == 1 && abs(c[0]) < eps)
        throw std::domain_error("Bad tolerance");
}

inline double ChebyshevApproximation::operator()(double x) const {
    
}




#endif