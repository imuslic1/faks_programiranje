#ifndef CHEBYSHEV_APPROXIMATION
#define CHEBYSHEV_APPROXIMATION
#define PI 4*atan(1)

#include <vector>
#include <cmath>
#include <stdexcept>

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

<<<<<<< HEAD
    for(int k = m-3; k>=0; --k) {
        cprim[k] = cprim[k+2] + mi*(k+1)*c[k+1];
    }
    ChebyshevApproximation to_return(cprim, xmin, xmax);   
=======
    for(int k = m-3; k>=0; --k)
        cprim[k] = cprim[k+2] + mi*(k+1)*c[k+1];   
>>>>>>> 7e4d902ee810ff771f217f507dcc4e3b9126bd4b

    return ChebyshevApproximation(cprim, xmin, xmax, m, n);
}

ChebyshevApproximation ChebyshevApproximation::antiderivative() const {
<<<<<<< HEAD
    std::vector<double> cint(this->m+2); //cint[0] = 0
    double mi = (xmax-xmin) / 4;
    
    for(int k=1; k<=m-1; ++k) {
        cint[k] = mi*(c[k-1]-c[k+1])/k;
    }
=======
    std::vector<double> cint(this->n+2); //cint[0] = 0
    double mi = (xmax-xmin) / 4;    
>>>>>>> 7e4d902ee810ff771f217f507dcc4e3b9126bd4b
    cint[0] = 0;
    cint[m] = mi * c[m-1]/m;
    cint[m+1] = mi * (c[m]/(m+1));        //k=m+1 => m=k-1

<<<<<<< HEAD
    ChebyshevApproximation to_return(cint, xmin, xmax); 
    return to_return;
=======
    for(int k=1; k<=m-1; ++k)
        cint[k] = mi*(c[k-1]-c[k+1])/k;

    return ChebyshevApproximation(cint, xmin, xmax, m, n);
>>>>>>> 7e4d902ee810ff771f217f507dcc4e3b9126bd4b
}

double ChebyshevApproximation::integrate(double a, double b) const {
    if(a<xmin || b>xmax)
        throw std::domain_error("Bad Interval");
    auto integral = this->antiderivative();
    return integral(b) - integral(a);
}

double ChebyshevApproximation::integrate() const {
    auto integral = this->antiderivative();
    return integral(xmax) - integral(xmin);
}

#endif