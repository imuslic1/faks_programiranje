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
};

void Vector::Ispisi() {
    for(auto a: v) std::cout<<a;                //probna funkcija za ispis
}

Vector::Vector(std::initializer_list<double> l) {
    if(l.size()==0) throw std::range_error("Bad dimension");
    v = l;
}

double &Vector::operator[](int i) {
    return v[i];
}

double Vector::operator[](int i) const {
    return v[i];
}

double &Vector::operator()(int i) {
    if(i>v.size() || i<0) throw std::range_error("Invalid index");
    return v[i-1];
}

double Vector::operator()(int i) const {
    if(i>v.size() || i<0) throw std::range_error("Invalid index");
    return v[i-1];
}

double Vector::Norm() const {
    long double sumakv = 0;
    for(auto a : v) sumakv+=a;
    return sqrt(sumakv);
}

double VectorNorm(const Vector &v) {
    long double sumakv = 0;              //mozda ne treba long
    for(auto a : v.v) sumakv+=a;
    return sqrt(sumakv);
}

double Vector::GetEpsilon() const {
    long double norma = this->Norm();    //potencijalno bez long
    return 10 * norma * std::numeric_limits<double>::epsilon();
}



