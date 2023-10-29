#include <bits/stdc++.h>

/**
 * Numerički Algoritmi - Zadaća 1
 *    Vector.h - omotač oko bibliotečkog
 *    std::vector<double>
*/

class Vector {
    std::vector<double> v;
public:
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
    friend Vector operator/(const Vector &v, double s);
    Vector &operator/=(double s);
};

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

inline void Vector::Print(char separator = '\n', double eps = -1) const {
    if(eps<0) eps = this->GetEpsilon();
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

/**
 * Numerički Algoritmi - Zadaća 1
 *    Matrix.h - klasna matrica
 *    organizirana kao std::vector<std::vector<double>>
*/

class Matrix {
    std::vector<std::vector<double>> matrica;
public:
    Matrix(){}
    Matrix(int m, int n);
    Matrix(const Vector &v);
    Matrix(std::initializer_list<std::vector<double>> l);
    int NRows() const;
    int NCols() const;
    double *operator[](int i);
    const double *operator[](int i) const;
    double &operator()(int i, int j);
    double operator()(int i, int j) const;
    double Norm() const;
    friend double MatrixNorm(const Matrix &m);
    double GetEpsilon() const;
    void Print(int width = 10, double eps = -1) const;
    friend void PrintMatrix(const Matrix &m, int width, double eps);
    friend Matrix operator +(const Matrix &m1, const Matrix &m2);
    Matrix &operator +=(const Matrix &m);
    friend Matrix operator -(const Matrix &m1, const Matrix &m2);
    Matrix &operator -=(const Matrix &m);
    friend Matrix operator *(double s, const Matrix &m);
    friend Matrix operator *(const Matrix &m, double s);
    Matrix &operator *=(double s);
    friend Matrix operator *(const Matrix &m1, const Matrix &m2);
    Matrix &operator *=(const Matrix &m);
    friend Vector operator *(const Matrix &m, const Vector &v);
    friend Matrix Transpose(const Matrix &m);
    void Transpose();
};

inline Matrix::Matrix(int m, int n) {
    if(m<=0 || n<=0) 
        throw std::range_error("Bad dimension");
    matrica = std::vector<std::vector<double>>(m, std::vector<double>(n, 0));
}

inline Matrix::Matrix(const Vector &v) {
    for(int i=0; i<matrica.at(0).size(); i++) {
        matrica.at(0).at(i) = v[i];
    }
}
inline Matrix::Matrix(std::initializer_list<std::vector<double>> l) {
    if(l.size()==0 || l.begin()->size()==0) throw std::range_error("Bad dimension");
    size_t common_size = l.begin()->size(); 
    for(auto a:l) 
        if(a.size()!=common_size) 
            throw std::logic_error("Bad matrix");
            //provjeriti da li je orazan vektor pa baciti bad dimension
    matrica = l;
}

inline int Matrix::NRows() const { return matrica.size(); }
inline int Matrix::NCols() const { return matrica.at(0).size(); }

inline double *Matrix::operator[](int i) {
    return &matrica[i][0];
    //cekiraj AT 32
}

inline const double *Matrix::operator[](int i) const {
    return &matrica[i][0];
}

inline double &Matrix::operator()(int i, int j) {
    if(i<0 || i>NRows() || j<0 || j>NCols())
        throw std::range_error("Invalid index");
    //provjeriti validnost i i j, baciti izuzetak ako treba
    int _i = i-1, _j = j-1;
    return matrica[_i][_j];
    }

inline double Matrix::operator()(int i, int j) const {
    //const verzija operatora odozgo
    if(i<0 || i>NRows() || j<0 || j>NCols())
        throw std::range_error("Invalid index");
    //provjeriti validnost i i j, baciti izuzetak ako treba
    int _i = i-1, _j = j-1;
    return matrica[_i][_j];
}

/**
 * Matrix::Norm() const
 * Vanjska ranged for-petlja ide kroz
 * redove (vectore), unutrašnja kroz elemente
 * vectora. a je vector, b je double u vectoru
 * 
 * Isto se primjenjuje na jos par mjesta nize u kodu
*/

inline double Matrix::Norm() const {
    auto kopija = *this;
    std::sort(kopija.matrica.begin(), kopija.matrica.end());
    long double sumakv=0;
    for(auto a:matrica)
        for(auto b:a)
            sumakv+=b*b;
    return sqrt(sumakv);
}

inline double Matrix::GetEpsilon() const {
    long double norma = this->Norm();
    return 10. * norma * std::numeric_limits<double>::epsilon();
}

inline double MatrixNorm(const Matrix &m) {
    return m.Norm();
}

inline void Matrix::Print(int width, double eps) const {
    if(eps<0) eps=this->GetEpsilon();
    for(auto a:matrica) {
        for(auto b:a) {
            if(fabs(b) < eps) std::cout<<std::setw(width)<<"0";
            else std::cout<<std::setw(width)<<b;
            }
        std::cout<<std::endl;
    }
}

inline void PrintMatrix(const Matrix &m, int width=10, double eps=-1) {
    if(eps<0) eps=m.GetEpsilon();
    for(auto a:m.matrica) {
        for(auto b:a) {
            if(fabs(b) < eps) std::cout<<"0";
            else std::cout<<std::setw(width)<<b;
            }
        std::cout<<std::endl;
    }
}

inline Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if(m1.NRows() != m2.NRows() || m2.NCols() != m2.NCols())
        throw std::domain_error("Incompatible formats");
    Matrix rezultat(m1.NRows(), m1.NCols());
    for(int i=0; i<m1.NRows(); i++)
        for(int j=0; j<m1.NCols(); j++)
            rezultat.matrica[i][j] = m1.matrica[i][j] + m2.matrica[i][j];
    return rezultat;
}

inline Matrix operator-(const Matrix &m1, const Matrix &m2) {
    if(m1.NRows() != m2.NRows() || m2.NCols() != m2.NCols())
        throw std::domain_error("Incompatible formats");
    Matrix rezultat(m1.NRows(), m1.NCols());
    for(int i=0; i<m1.NRows(); i++)
        for(int j=0; j<m1.NCols(); j++)
            rezultat.matrica[i][j] = m1.matrica[i][j] - m2.matrica[i][j];
    return rezultat;
}

inline Matrix operator*(double s, const Matrix &m) {
    Matrix rezultat = m;
    //trebalo bi biti okej, AT 31
    for(int i=0; i<rezultat.NRows(); i++) {
        for(int j=0; j<rezultat.NCols(); j++) {
            rezultat.matrica[i][j] *= s;
        }
    }
    return rezultat;
}

inline Matrix operator*(const Matrix &m, double s) {
    return s*m;
}

inline Matrix operator*(const Matrix &m1, const Matrix &m2) {
    if(m1.NCols()!=m2.NRows())
        throw std::domain_error("Incompatible formats");
    Matrix rezultat(m1.NRows(), m2.NCols());
    for (int i=0; i<m1.NRows(); i++) {
        for (int j=0; j<m2.NCols(); j++) {
            for (int k=0; k<m1.NCols(); k++) {
                rezultat.matrica[i][j] += m1.matrica[i][k] * m2.matrica[k][j];
            }
        }
    }
    return rezultat;    
}

inline Vector operator*(const Matrix &m, const Vector &v) {
    if(m.NCols()!=v.NElems())
        throw std::domain_error("Incompatible formats");
    Vector rezultat(m.NRows());
    for (int i=0; i<m.NRows(); i++) {
        for (int j=0; j<1; j++) {
            for (int k=0; k<m.NCols(); k++) {
                rezultat[i] += m.matrica[i][k] * v[k];
            }
        }
    }
    return rezultat;
}

inline Matrix &Matrix::operator+=(const Matrix &m) {
    if(this->NRows() != m.NRows() || this->NCols() != m.NCols())
        throw std::domain_error("Incompatible formats");
    for(int i=0; i<NRows(); i++)
        for(int j=0; j<NCols(); j++)
            this->matrica[i][j] += m.matrica[i][j];
    return *this;
}

inline Matrix &Matrix::operator-=(const Matrix &m) {
    if(this->NRows() != m.NRows() || this->NCols() != m.NCols())
        throw std::domain_error("Incompatible formats");
    for(int i=0; i<NRows(); i++)
        for(int j=0; j<NCols(); j++)
            this->matrica[i][j] -= m.matrica[i][j];
    return *this;
}

inline Matrix &Matrix::operator*=(double s) {
    for(auto &a:this->matrica)
        for(auto &b:a)
            b*=s;
    return *this;
}

inline Matrix &Matrix::operator*=(const Matrix &m) {
    if(this->NCols()!=m.NRows())
        throw std::domain_error("Incompatible formats");
    Matrix rezultat(this->NRows(), m.NCols());
    for (int i=0; i<this->NRows(); i++) {
        for (int j=0; j<m.NCols(); j++) {
            for (int k=0; k<this->NCols(); k++) {
                rezultat.matrica[i][j] += this->matrica[i][k] * m.matrica[k][j];
            }
        }
    }
    *this = rezultat;
    return *this;   
}

inline Matrix Transpose(const Matrix &m) {
    Matrix transponirana(m.NCols(), m.NRows());
        for(int i=0; i<m.NCols(); i++){
        for(int j=0; j<m.NRows(); j++) {
                transponirana.matrica[i][j] = m.matrica[j][i];
        }
    }
    return transponirana;
}

inline void Matrix::Transpose() {
    if(this->NRows()!= this->NCols()) {
         Matrix transponirana(this->NCols(), this->NRows());
        for(int i=0; i<this->NCols(); i++){
        for(int j=0; j<this->NRows(); j++) {
                transponirana.matrica[i][j] = this->matrica[j][i];
        }
    }
    *this = transponirana;
    }
    else {
        for(int i=0; i<NRows(); i++){
        for(int j=i; j<NCols(); j++) {
            if(i!=j) {
                double temp;
                temp = matrica[i][j];
                matrica[i][j] = matrica[j][i];
                matrica[j][i] = temp;
            }
        }
    }
    }
}

/**
 * Numerički Algoritmi - Zadaća 1
 *  Main funkcija - aplikativni testovi
*/

int main() {
    try {
        Vector a(3);
        Vector b(3);
        for(int i=0; i<3; i++) {
            double x; std::cin>>x;
            a[i]=x;
            b[i]=x;
        }
        
        std::cout<<"\n***TEST1: A+=B***\n"; a+=b;
        a.Print(); std::cout<<"\n"; b.Print(); std::cout<<"\n***TEST2: operator*(3, a)\n";
        a=operator*(3, a);
        a.Print(); std::cout<<"\nTEST3: B*=3\n";
        b*=3; b.Print();

        //std::cout<<"\n***TEST4: 0DIV EXCEPT:***\n";
        //operator/(0, b);

        Matrix matrica(2, 3);
        //Matrix matrica2 = {{1, 2}, {1, 2, 3}}; //test sekvencijalnog konstruktora
        //std::cout<<"***debug 001: vracanje reda matrice***\n";
        int foo = matrica.NCols();
        for(double* i = matrica[1]; i<matrica[1]+foo; i++)
            std::cout<<*i;
        std::cout<<"\n"<<matrica.Norm()<<"\n";
        matrica.Print();
        std::cout<<"\nMNOZENJE MATRICE VEKTOROM: \n";
        Vector v = {1, 2, 3};
        Matrix A = {{1, 2, 3}, {2, 1, 1}, {4, 3, 2}};
        Matrix B = {{1, 2}, {3, 6}, {7, 9}, {5, 2}};
        auto rezultat_mnozenja = A*v;
        rezultat_mnozenja.Print();
        getchar();
        std::cout<<"\nTRANSPONUJ A: \n";
        A.Transpose(); A.Print();
        std::cout<<"\n";
        Matrix C = Transpose(A); C.Print();
        C*=3; C.Print();
        std::cout<<"\nTRANSPONUJ B: \n";
        //B.Transpose(); B.Print();
        //Transpose(B); B.Print();
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    return 0;
}