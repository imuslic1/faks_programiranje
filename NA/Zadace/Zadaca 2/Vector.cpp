#include "Vector.h"

/**
 * @brief implementacija metoda klase Vector.h
*/

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

/**
 * Vector::Norm()
 * Zbog vece preciznosti pri sabiranju manjih elemenata ka vecim
 * koristi se std::sort()
*/

inline double Vector::Norm() const {
    long double sumakv = 0; auto v1 = this->v;
    std::sort(v1.begin(), v1.end());      
    for(auto a : v1) sumakv+=a*a;
    return sqrt(sumakv);
}

inline double VectorNorm(const Vector &v) {
    return v.Norm();
}

inline double Vector::GetEpsilon() const {
    long double norma = this->Norm();    //potencijalno bez long
    return 10. * norma * std::numeric_limits<double>::epsilon();
}

inline void Vector::Print(char separator, double eps) const {
    if(eps<0) eps = this->GetEpsilon();
    for(int i=0; i<v.size(); i++) {
        double trenutni = v.at(i);
        if(fabs(trenutni)<eps) trenutni = 0;
        if(i==v.size()-1 && separator != '\n') std::cout<<trenutni;
        else std::cout<<trenutni<<separator;
    }
}


inline Vector operator+(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    Vector rezultat(v1.v.size());
    for(int i=0; i<v1.v.size(); i++)
        //rezultat.v.push_back(v1.v.at(i)+v2.v.at(i));
        rezultat.v.at(i)=v1.v.at(i)+v2.v.at(i);
    return rezultat;    
}

inline Vector operator-(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    Vector rezultat(v1.v.size());
    for(int i=0; i<v1.v.size(); i++)
        //rezultat.v.push_back(v1.v.at(i)-v2.v.at(i));
        rezultat.v.at(i)=v1.v.at(i)-v2.v.at(i);
    return rezultat;            
}

inline Vector operator*(double s, const Vector &v) {
    Vector rezultat(v.v.size());
    for(int i=0; i<v.v.size(); i++) 
        rezultat.v.at(i)=v.v.at(i)*s;
    return rezultat;        
}

inline Vector operator*(const Vector &v, double s) {
    return s*v;
}

inline double operator*(const Vector &v1, const Vector &v2) {
    if(v1.v.size()!=v2.v.size())
        throw std::domain_error("Incompatible formats");
    double result=0;
    for(int i=0; i<v1.v.size(); i++)
        result+=v1.v.at(i)*v2.v.at(i);
    return result;
}

inline Vector operator/(const Vector &v, double s) {
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

inline void Vector::Chop(double eps) {
    if(eps<0) eps = this->GetEpsilon();
    int velicina = this->NElems();
    for(auto a : this->v)
        if(std::fabs(a) < eps) a=0;
    /*for(int i=0; i<velicina; i++) ISTO JE KO OVO
        if(std::fabs(this->v[i])<eps) this->v[i] = 0;*/
}

inline bool Vector::EqualTo(const Vector &v, double eps) const {
    if(this->v.size()!=v.NElems()) return false;
    if(eps<0) eps= this->GetEpsilon();
    int velicina = this->NElems();
    for(int i=0; i<velicina; i++)
        if(std::fabs(this->v[i] - v[i]) > eps) return false;
    return true;
}