#include <bits/stdc++.h>

class Vector {
    std::vector<double> v;
public:
    void Ispisi(); //probna funkcija za ispis

    explicit Vector(int n) {
        if(n<=0) throw std::range_error("Bad dimension");
        v = std::vector<double>(n, 0);
    }  

    Vector(std::initializer_list<double> l);
    int NElems() const { return v.size(); }
    double &operator[](int i);
    double operator[](int i) const;
    double &operator()(int i);
    double operator()(int i) const;
    double Norm() const;
    friend double VectorNorm(const Vector &v);
    double GetEpsilon() const;
    void Print(char separator, double eps) const;
    friend void PrintVector(const Vector &v, char separator, 
        double eps);
    friend Vector operator+(const Vector &v1, const Vector &v2);
    Vector &operator +=(const Vector &v);
    friend Vector operator-(const Vector &v1, const Vector &v2);
    Vector &operator-=(const Vector &v);
    friend Vector operator*(double s, const Vector &v);
    friend Vector operator*(const Vector &v, double s);
    Vector &operator*=(double s);
    friend double operator*(const Vector &v1, const Vector &v2);
    friend Vector operator/(double s, const Vector &v);
    Vector &operator/=(double s);
};

inline void Vector::Ispisi() {
    for(auto a: v) std::cout<<a;                //probna funkcija za ispis
}

inline Vector::Vector(std::initializer_list<double> l) {
    if(l.size()==0) throw std::range_error("Bad dimension");
    v = l;
}

inline double &Vector::operator[](int i) {
    return v[i];
}

inline double Vector::operator[](int i) const {
    return v[i];
}

inline double &Vector::operator()(int i) {
    if(i>v.size() || i<0) throw std::range_error("Invalid index");
    return v[i-1];
}

inline double Vector::operator()(int i) const {
    if(i>v.size() || i<0) throw std::range_error("Invalid index");
    return v[i-1];
}

inline double Vector::Norm() const {
    long double sumakv = 0;
    for(auto a : v) sumakv+=a;
    return sqrt(sumakv);
}

inline double VectorNorm(const Vector &v) {
    long double sumakv = 0;              //mozda ne treba long
    for(auto a : v.v) sumakv+=a;
    return sqrt(sumakv);
}

inline double Vector::GetEpsilon() const {
    long double norma = this->Norm();    //potencijalno bez long
    return 10 * norma * std::numeric_limits<double>::epsilon();
}

inline void Vector::Print(char separator = '\n', double eps = -1) const {
    if(eps<=0) eps = this->GetEpsilon();
    for(int i=0; i<v.size(); i++) {
        double trenutni = v.at(i);
        if(fabs(trenutni)<eps) trenutni = 0;
        if(i==v.size()-1 && separator != '\n') std::cout<<trenutni;
        else std::cout<<trenutni<<separator;
    }
}

inline void PrintVector(const Vector &v, char separator = '\n', 
    double eps = -1) {
    if(eps<=0) eps = v.GetEpsilon();
    for(int i=0; i<v.v.size(); i++) {
        double trenutni = v.v.at(i);
        if(fabs(trenutni)<eps) trenutni = 0;
        if(i==v.v.size()-1 && separator != '\n') std::cout<<trenutni;
        else std::cout<<trenutni<<separator;
    }
}

inline Vector operator+(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    Vector rezultat(v1.v.size());
    for(int i=0; i<v1.v.size(); i++)
        rezultat.v.push_back(v1.v.at(i)+v2.v.at(i));
    return rezultat;    
}

inline Vector operator-(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    Vector rezultat(v1.v.size());
    for(int i=0; i<v1.v.size(); i++)
        rezultat.v.push_back(v1.v.at(i)-v2.v.at(i));
    return rezultat;            
}

inline Vector operator*(double s, const Vector &v) {
    Vector rezultat(v.v.size());
    for(int i=0; i<v.v.size(); i++) 
        rezultat.v.at(i)=v.v.at(i)*s;
    return rezultat;        
}

inline Vector operator*(const Vector &v, double s) {
    return operator*(s, v);
}

inline double operator*(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    double result=0;
    for(int i=0; i<v1.v.size(); i++)
        result+=v1.v.at(i)*v2.v.at(i);
    return result;
}

inline Vector operator/(double s, const Vector &v) {
    if(s==0)
        throw std::domain_error("Division by zero");
    auto rezultat = v; 
    for(auto &a:rezultat.v) a/=s;
    return rezultat;
}

inline Vector &Vector::operator+=(const Vector &v) {
    if(this->v.size()!=v.v.size())
        throw std::domain_error("Incompatible formats");
    for(int i=0; i<this->v.size(); i++) {
        this->v.at(i)+=v.v.at(i);
    }
    return *this;
}

inline Vector &Vector::operator-=(const Vector &v) {
    if(this->v.size()!=v.v.size())
        throw std::domain_error("Incompatible formats");
    for(int i=0; i<this->v.size(); i++) {
        this->v.at(i)-=v.v.at(i);
    }
    return *this;
}

inline Vector &Vector::operator*=(double s) {
    for(auto &a:this->v) a*=s;
    return *this;
}

inline Vector &Vector::operator/=(double s) {
    if(s==0) throw std::domain_error("Division by zero");
    for(auto &a:this->v) a/=s;
    return *this;
}