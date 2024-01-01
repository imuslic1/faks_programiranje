#include <iostream>
#include <limits>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>

/**
 * @brief Abstract class for other types of Interpolator classses to be derived from
 * 
 */
class AbstractInterpolator {
    mutable int lastLocated;
    /**
     * @brief Checks whether the given parameter x is in the interval (index, index+1]
     * 
     * @param x value to check for
     * @param index starting index of the interval
     * @return true if x is in the interval,
     * @return false if x is not in the interval
     */
    inline bool inInterval(double x, int index) const {
        if(index<0 || index+1 >= data.size())
            return false;
        return x > data.at(index).first && x <= data.at(index+1).first;
    }

protected: 
    std::vector<std::pair<double, double>> data;
    /**
     * @brief Locates the given parameter x and stores the interval (xi, xi+1] of indexes internally into the class object.
     * 
     * @param x value to be located
     * @return int index of located value. 0 if x <= x1 from data, n if x > xn from data.
     */
    int Locate(double x) const;
public:
    /**
     * @brief Prints the data points given to the Interpolator.
     */
    void printData() const;
    
    /**
     * @brief Construct a new Abstract Interpolator:: Abstract Interpolator object
     * 
     * @param data Points (x, y) to be added as data entries for interpolation
     */
    AbstractInterpolator(const std::vector<std::pair<double, double>> &data);
    
    virtual double operator()(double x) const = 0;
};

inline AbstractInterpolator::AbstractInterpolator(const std::vector<std::pair<double, double>> &data) {
    lastLocated = 1;
    std::vector<std::pair<double, double>> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const std::pair<double, double> &p1, 
        const std::pair<double, double> &p2) {
            if(p1.first == p2.first)
                throw std::domain_error("Invalid data set");
        return p1.first<p2.first;
    });
    this->data = sortedData;
}

inline int AbstractInterpolator::Locate(double x) const {
    int n = data.size()-1;
    //if x is less than the first element
    if(x<=data.at(0).first) {
        lastLocated = 0;
        return 0;
    }
    //if x is greater than the last element
    if(x>data.at(n).first) {
        lastLocated = n;
        return n+1;
    }   
    //Check if x is in the last interval
    if(inInterval(x, lastLocated)) {
        return lastLocated+1;
    }   
    //Check if x is in the interval previous to the last interval
    if(inInterval(x, lastLocated-1)) {
        --lastLocated;
        return lastLocated+1;
    }
    //Check if x is in the interval following the last interval
    if(inInterval(x, lastLocated+1)) {
        ++lastLocated;
        return lastLocated+1;
    }   
    //Binary search
    auto it = std::lower_bound(data.cbegin(), data.cend(), x,
        [](const std::pair<double, double> &pair, double x) {
            return pair.first < x;
        });
    //Update the interval
    lastLocated = it-data.cbegin();
    return lastLocated;
}

inline void AbstractInterpolator::printData() const {
    for(int i=0; i<this->data.size(); ++i)
        std::cout<<"{"<<this->data.at(i).first<<", "<<this->data.at(i).second<<"} ";
}

class LinearInterpolator : public AbstractInterpolator {
public:

    LinearInterpolator(const std::vector<std::pair<double,double>> &data)
        : AbstractInterpolator(data){}
    double operator()(double x) const override {
        int interval = Locate(x);

        std::pair<long double, long double> point_i;
        std::pair<long double, long double> point_iplus1;

        if(interval == 0) {
            point_i = data.at(0);
            point_iplus1 = data.at(1);
        }

        else if(interval == data.size()) {
            point_i = data.at(data.size()-2);
            point_iplus1 = data.at(data.size()-1);
        }
        else {
            point_i = data.at(interval-1);
            point_iplus1 = data.at(interval);
        }

        long double x1 = point_i.first;
        long double x2 = point_iplus1.first;
        long double y1 = point_i.second;
        long double y2 = point_iplus1.second;

        double result = (x2-x) / (x2-x1) * y1 + (x-x1) / (x2-x1) * y2;

        return result;
    }
};

class PolynomialInterpolator : public AbstractInterpolator {
private:
    std::vector<double> newtonsCoefficients;
    std::vector<double> dodatneVrijednosti;
public:
    explicit PolynomialInterpolator(const std::vector<std::pair<double, double>> &data) : AbstractInterpolator(data) {
        for (const auto &tacka : data) {
            newtonsCoefficients.push_back(tacka.second);
        }

        int n = this->data.size();

        for (int j=1; j<=n-1; j++) {
            for (int i=n; i>=j+1; i--) {
                if(i==n) 
                    dodatneVrijednosti.push_back(newtonsCoefficients.at(i-1));
                newtonsCoefficients.at(i - 1) = (newtonsCoefficients.at(i-1)
                 - newtonsCoefficients.at(i-1-1)) / (data.at(i-1).first - data.at(i-j-1).first);
            }
        }
    }

    double operator()(double x) const override {
        int n = data.size();
        long double f = newtonsCoefficients.at(n - 1);
        for (int i=n-1; i>=1; i--) {
            f = f * (x-data.at(i-1).first) + newtonsCoefficients.at(i-1);
        }
        return (double) f;
    }

    void AddPoint(const std::pair<double, double> &p) {
        const double epsilon = 1e-15;
        for(auto &i : data)
            if(fabs(i.first - p.first) < epsilon) 
                throw std::domain_error("Invalid point");
        
        int n = data.size();

        data.push_back(p);

        std::vector<double> y_nplus1(n);
        y_nplus1.at(0) = p.second;

        const std::vector<double> &y_n = dodatneVrijednosti;
        
        for(int j=1; j<n; j++)
            y_nplus1.at(j) = (y_nplus1.at(j-1)-y_n.at(j-1)) / (data.at(n).first-data.at(n-j).first);
        
        double newNewtonCoefficient = 
            (y_nplus1.at(n-1) - newtonsCoefficients.at(n-1)) / (data.at(n).first - data.at(0).first);
        
        newtonsCoefficients.push_back(newNewtonCoefficient);
        dodatneVrijednosti = std::vector<double>(y_nplus1);
    }

    std::vector<double> GetCoefficients() const {
        int n = data.size();
        //koeficijenti polinoma interpolacije
        std::vector<double> koeficijenti(n, 0.0);
        //koeficijenti master polinoma
        std::vector<long double> w(n+1), v(n+1);
        w.at(0) = 1;
        for(int i=1; i<=n; i++) {
            w.at(i) = w.at(i-1);
            for(int j=i-1; j>0; j--)
                w.at(j) = w.at(j-1)-data.at(i-1).first*w.at(j);
            w.at(0) = -data.at(i-1).first * w.at(0);
        }        
        //koeficijent alfa, racunanje koeficijenata polinoma
    	for(int i=0; i<n; i++) {
            long double alfa = 1.0;
            for(int j=0; j<n; j++)
                if(j!=i) 
                    alfa *= data.at(i).first - data.at(j).first;
            alfa = data.at(i).second / alfa;

            for(int j=0; j<=n; j++) v[j] = w[j];
            for(int j=n-1; j>=0; j--) {
                v.at(j) += data.at(i).first * v.at(j+1);
                koeficijenti.at(j) += alfa * v.at(j+1); 
            }     
        }
        return koeficijenti;
    }
};

class PiecewisePolynomialInterpolator : public AbstractInterpolator {
private: 
    int order;
public:
    explicit PiecewisePolynomialInterpolator(const std::vector<std::pair<double, double>> &data, int order) 
            : AbstractInterpolator(data) {
        if(order<1||order>=data.size())
            throw std::domain_error("Invalid order");
        this->order = order;
    }

    double operator() (double x) const override {
        int subinterval = Locate(x);
        int lower = 0, upper = 0;

        if(order%2 == 0) {
            lower = subinterval-order/2;
            upper = subinterval+order/2;
        } else {
            lower = subinterval - (order-1)/2;
            upper = subinterval + (order+1)/2;
        }

        if(lower <= 0) {
            lower = 1;
            upper = order+1;
        }
        if(upper>data.size()) {
            upper = data.size();
            lower = upper - order;
        }

        long double sum = 0;

        for(int i= lower-1; i<upper; i++) {
            long double proizvod = data.at(i).second;
            for(int j = lower-1; j<upper; j++) 
                if(j!=i)
                    proizvod*=(x-data.at(j).first) / (data.at(i).first - data.at(j).first);
            sum += proizvod;
        }
        return (double) sum;
    }
};

class SplineInterpolator : public AbstractInterpolator {
private: 
    std::vector<double> r, s, q;
public:
    explicit SplineInterpolator(
        const std::vector<std::pair<double, double>> &data) 
        : AbstractInterpolator(data) {
    r.resize(this->data.size());
    r[0] = 0;
    r[this->data.size() -1] = 0;

    std::vector<double> alpha (r.size() - 2);

    for (int i=1; i<r.size()-1; i++) {
            alpha[i-1] = 2 * (this->data[i+1].first - this->data[i-1].first);
            r[i] = 3 * ((this->data[i+1].second - this->data[i].second) / (this->data[i+1].first - this->data[i].first)
                    - (this->data[i].second - this->data[i-1].second) 
                    / (this->data[i].first - this->data[i-1].first));
        }

        for (int i=1; i<r.size()-2; i++) {
            double mi = (this->data[i+1].first - this->data[i].first) / alpha[i-1];
            alpha[i] = alpha[i] - mi * (this->data[i+1].first - this->data[i].first);
            r[i+1] = r[i+1] - mi*r[i];
        }

        r[r.size()-2] = r[r.size()-2] / alpha[r.size()-3];

        for (int i=r.size()-3; i>=1; i--)
            r[i] = (r[i] - (this->data[i+1].first - this->data[i].first) * r[i+1]) / alpha[i-1];

        for (int i=0; i<r.size()-1; i++) {
            double delta = this->data[i+1].first - this->data[i].first;
            s.push_back((r[i+1] - r[i]) / (3*delta));
            q.push_back((this->data[i+1].second - this->data[i].second) / delta-delta*(r[i+1] + 2*r[i]) / 3);
        }
    }

    double operator()(double x) const override {
        int index = Locate(x);
        if(index==0) ++index;
        else if(index==data.size()) --index;
        long double t = x - data.at(index-1).first;
        double Px = data.at(index-1).second + t*(q.at(index-1) + t*(r.at(index-1)+ t*s.at(index-1)));
        return Px;
    }
};

class TrigonometricInterpolator : public AbstractInterpolator {
private:
    double omega, T;
public:
    inline explicit TrigonometricInterpolator(const std::vector<std::pair<double, double>> &data) : AbstractInterpolator(data) {
        const double epsilon = 1e-15;
        if(std::fabs(data.at(0).second - data.at(data.size()-1).second) < epsilon)
            throw std::domain_error("Function is not periodic");
    }

    double operator()(double x) const override {
        double sum = 0.0;

        for (size_t k = 0; k < data.size(); ++k) {
            double ak = data.at(k).second;

            double factor = 1.0;
            for (size_t j = 0; j < data.size(); ++j) {
                if (j != k) {
                    double numerator = sin((x - data.at(j).first) * omega / 2);
                    double denominator = sin((data.at(k).first - data.at(j).first) * omega / 2);
                    factor *= numerator / denominator;
                }
            }

            sum += ak * factor;
        }

        return sum;
    }
};

class BarycentricInterpolator : public AbstractInterpolator {
private:
    std::vector<double> tezinskiKoeficijenti;
public:
    BarycentricInterpolator(const std::vector<std::pair<double, double>> &data, int order) : AbstractInterpolator(data) {
        if(order < 0 || order > data.size())
            throw std::domain_error("Invalid order");

        int n = this->data.size();
        
        tezinskiKoeficijenti.resize(n, 0.0);
        
        for(int i=0; i<n; i++) {
            tezinskiKoeficijenti[i] = 0.0;
            double p = 1;
            for(int k = std::max(0, i-order); k <= std::min(i, n-order); k++) {
                p=1;
                for(int j = k; j<k+order; j++) {
                    if(j!=i)
                        p /= (data.at(i).first-data.at(j).first);
                }
                if(k%2 == 1)
                    p = -p;
                
            }
            tezinskiKoeficijenti.at(i) += p;
        }
    }

    double operator()(double x) const override {
        double p = 0, q = 0, n=this->data.size();
        long double epsilon = 1e-15;
        for(int i=0; i<n; i++) {
            if(std::fabs(x - data.at(i).first) < epsilon)
                return data.at(i).second;
            double u = tezinskiKoeficijenti.at(i) / (x - data.at(i).first);
            p += u*data.at(i).second;
            q += u;
        }
        return p/q;
    }
    std::vector<double> GetWeights() const {
        return tezinskiKoeficijenti;
    }
};

double TestTrig(double x) {
    return sin(x);
}

double TestPoly(double x) {
    return 3*x*x*x + x*x - 2*x;  
}

double TestLin(double x) {
    return 0.253688*x + 0.17;
}


int main() {
    std::vector<std::pair<double, double>> data = 
        {{-4, 0}, {-3.25, -2.25}, {1.5, 2.5}, {4, 0}};
    LinearInterpolator li(data);
    std::cout<<"\nLinearna Interpolacija funkcije u tački 5: ";
    std::cout<<li(5);
    std::cout<<"\nVrijednost funkcije u tački 5: "<<TestLin(5)<<std::endl;

    std::vector<std::pair<double, double>> data2 = {{0,0},
                                                    {0.3,   -0.429},
                                                    {0.5, -0.3749},
                                                    {-0.75,   0.797},                                                    
                                                    {-1, 0},
                                                    {-0.5, 0.875}
                                                    };
    
    PolynomialInterpolator PI(data2);
    PI.AddPoint({1, 2});
    PI.AddPoint({-0.16, 0.3333333333333});
    std::cout<<"\nPolinomska Interpolacija funkcije u tački .1: ";
    std::cout << PI(0.1);
    std::cout<<"\nVrijednost funkcije u tački .1: "<<TestPoly(0.1)<<std::endl;

    double piTrig = 4*atan(1);
    std::vector<std::pair<double, double>> dataTrig;
    for(double i=0; i<(4.)*piTrig; i+=0.5*piTrig) {
        std::pair<double, double> add = std::make_pair(i, sin(i));
        dataTrig.push_back(add);
    }
    TrigonometricInterpolator ti(dataTrig);
    std::cout<<"\nTrigonometrijska Interpolacija funkcije sin x u tački pi/2: ";
    std::cout<<ti(piTrig/2.);
    std::cout<<"\nVrijednost funkcije sin x u tački pi/2: "<<sin(piTrig/2)<<std::endl;

    BarycentricInterpolator BI(data2, 1);
    std::cout<<"\nBaricentrična Interpolacija funkcije u tački .1: ";
    std::cout<<BI(0.1);
    std::cout<<"\nVrijednost funkcije u tački 1: "<<TestPoly(0.1)<<std::endl;

    SplineInterpolator SI(data2);
    std::cout<<"\nInterpolacija Splineom funkcije u tački .1: ";
    std::cout<<SI(0.1);
    std::cout<<"\nVrijednost funkcije u tački .1: "<<TestPoly(0.1)<<std::endl;

    PiecewisePolynomialInterpolator PPI(data2, 3);
    std::cout<<"\nPiecewise Interpolacija funkcije u tački .1: ";
    std::cout<<PPI(0.1);
    std::cout<<"\nVrijednost funkcije u tački .1: "<<TestPoly(0.1)<<std::endl;

    return 0;
}