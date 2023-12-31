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
    matrica = std::vector<std::vector<double>>(v.NElems(), std::vector<double>(1, 0));    
    for(int i=0; i<v.NElems(); i++) {
        matrica[i][0] = v[i];
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
    if((m1.NRows() != m2.NRows()) || (m1.NCols() != m2.NCols()))
        throw std::domain_error("Incompatible formats");
    Matrix rezultat(m1.NRows(), m1.NCols());
    for(int i=0; i<m1.NRows(); i++)
        for(int j=0; j<m1.NCols(); j++)
            rezultat.matrica[i][j] = m1.matrica[i][j] + m2.matrica[i][j];
    return rezultat;
}

inline Matrix operator-(const Matrix &m1, const Matrix &m2) {
    if((m1.NRows() != m2.NRows()) || (m1.NCols() != m2.NCols()))
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


int main() {

    /**
     * Numerički Algoritmi - Zadaća 1
     * Main funkcija - aplikativni testovi
     * 
     * 
     * Testovi konstruktora, 
     * nekonstantnih i konstantnih operatora [] i ()
     * te funkcije NElems()
     * 
    */

    std::cout<<"***TEST1: Vector***\n\n";
    std::cout<<"CETIRI IZUZETKA: \n";
    try {
        Vector nemoguci(-22);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        Vector nemoguci2 = {};
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    Vector a(3);
    Vector b = {2.1, 3.22, 4.57, 0.00014, 2.14159265359, 1.71};
    
    for(int i=0; i<a.NElems(); i++) {
        double x = 0.23; 
        a[i] = x + 0.4 * i;
    }

    for(int i=1; i<=b.NElems(); i++)
        b(i) += 1;

    try {
        std::cout<<b(-99);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        std::cout<<a(147);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }
    
    std::cout<<"\nVector a: \n{";
    for(int i=0; i<a.NElems(); i++) 
        std::cout<<a[i]<<"  ";
    std::cout<<"}\n";

    std::cout<<"\nVector b: \n{";
    for(int i=1; i<=b.NElems(); i++)
        std::cout<<b(i)<<"  ";
    std::cout<<"}\n";
    
    // Funkcije Norm(), VectorNorm(), i GetEpsilon:
    std::cout<<"\nNorma Vectora a: "<<a.Norm()<<"\n";
    std::cout<<"Norma Vectora b: "<<VectorNorm(b)<<"\n";
    std::cout<<"Epsilon (a) = "<<a.GetEpsilon()<<"\n";

    // Operatori +, -, * i /
            std::cout<<"\nCETIRI IZUTETKA:\n";

    try {
        PrintVector(a+b);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintVector(a-b);

    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        std::cout<<a*b;
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintVector(b/0);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }
    auto a1 = a*4;
    auto b1 = 0.7*b;
    std::cout<<"\nVector a1:\n"; a1.Print();
    std::cout<<"\nVector b1:\n"; b1.Print();
    std::cout<<"\na-a1:\n"; PrintVector(a-a1); 
    std::cout<<"\nb+b1:\n"; PrintVector(b+b1);
    std::cout<<"\nc = a*a1: \n"; std::cout<<a*a1<<"\n";
    std::cout<<"\na/0.2:\n"; PrintVector(a/0.4);

    // Testovi operatora +=, -=, *= i /=, funkcija Print() i PrintVector(),
    std::cout<<"\nTRI IZUTETKA:\n";
    try {
        a+=b;
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        a-=b;
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        a/=0;
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }  

    std::cout<<"\na-=a1:\n";
    a-=a1; a.Print();
    std::cout<<"\na+=a1:\n";
    a+=a1; b.Print();
    std::cout<<"\nb*=1.25:\n";
    b*=1.25; b.Print();
    std::cout<<"\nb/=0.9:\n";
    b/=0.9; b.Print();   
    
    std::cout<<"\n***TEST2: Matrix***\n";

    // Konstruktori, operator()    
    std::cout<<"\nPET IZUTETAKA:";
    try {
        Matrix A(0, 0);
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what();
    }
    
    try {
        Matrix B(-2, 0);
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what();
    }

    try {
        Matrix C({{1, 2}, {1, 2, 3}});
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what();
    }
    
    try {
        Matrix D({{}, {1, 2}});
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what();
    }

    try {
        Matrix E({});
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what()<<"\n";
    }
    
    std::cout<<"\nMatrica konstruisana vektorom: \n";
    const Vector u = {3.14, 2.71, 1.59, 2.08};
    u.Print();
    std::cout<<"\nbroj elemenata: "<<u.NElems()<<"\n";
    std::cout<<"\nmatrica:\n";
    Matrix w(u); w.Print(7);

    std::cout<<"\nDVA IZUZETKA: \n";
    try {
        std::cout<<w(-1, 14);
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what()<<"\n";
    }

    try {
        w(-10, 47) = 55.55775849;
    } catch(std::exception &e) {
        std::cout<<"\n"<<e.what()<<"\n";
    }
    std::cout<<"\nTest operatora(): \n";
    std::cout<<"w(2,1): "<<w(2, 1)<<"\n";
    w(2, 1) = 4.67;
    std::cout<<"w(2,1) = 4.67:\n"<<w(2, 1)<<"\n";

    Matrix matrica(2, 3);
    matrica = {{3.14, 2.71, 9.81}, {7.21, 2.20, 57.2958}};
    Matrix matrica2 = {{3.14, 2.71}, {7.21, 2.20}};
    // NCols(), NRows(), operator[], Print() 
    std::cout<<"\nMatrix A:\n"; matrica.Print(10);
    std::cout<<"\nMat A ima: "<<matrica.NRows()<<
        " reda i "<<matrica.NCols()<<" kolone.\n";
    std::cout<<"\nPrvi red Mat A:\n";
    
    int foo = matrica.NCols();
    for(double* i = matrica[0]; i<matrica[0]+foo; i++)
        std::cout<<*i<<"     ";
    std::cout<<"\nDvaput uvecan prvi red Mat A:\n";
    for(double* i = matrica[0]; i<matrica[0]+foo; i++)
        *i*=2;        
    for(double* i = matrica[0]; i<matrica[0]+foo; i++)
        std::cout<<*i<<"     ";
    std::cout<<"\n";

    // Norm(), GetEpsilon(), operator*=(), PrintMatrix()
    matrica2 *= 2.21;
    std::cout<<"\nMatrica B:\n"; PrintMatrix(matrica2, 9);
    std::cout<<"\nNorma Matrice A: "<<matrica.Norm()<<"\n";
    std::cout<<"Norma Matrice B: "<<MatrixNorm(matrica2)<<"\n";
    std::cout<<"Epsilon Matrice A: "<<matrica.GetEpsilon()<<"\n";
    std::cout<<"Epsilon Matrice B: "<<matrica2.GetEpsilon()<<"\n";    

    // Operatori +, -, *
    std::cout<<"\nCETIRI IZUZETKA: \n";
    try {
        PrintMatrix(matrica + matrica2);
        std::cout<<"\n";
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintMatrix(matrica-matrica2);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintMatrix(matrica*matrica2);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintMatrix(matrica2 * u);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }
    Vector v = {1.1, 2.2, 3.3};
    Matrix A = {{1.11, 2.22, 3.33}, {2.33, 1.22, 1.11}, {4.33, 3.22, 2.11}};
    Matrix B = {{1.99, 2.47}, {3.32, 6.64}, {7.88, 9.66}, {5.755, 2.666}};
    Matrix C = {{3.14, 1.61}, {2.71, 9.81}, {1.73, 1.41}};
    std::cout<<"\nMatrix A: \n"; A.Print(7);
    std::cout<<"\nMatrix B: \n"; B.Print(7);
    std::cout<<"\nMatrix C: \n"; C.Print(7);
    std::cout<<"\nVector v: \n"; v.Print(',');
    std::cout<<"\nA + A:\n"; PrintMatrix(A+A);
    std::cout<<"\nB - B:\n"; PrintMatrix(B-B);
    std::cout<<"\nA * C:\n"; PrintMatrix(A*C);
    std::cout<<"\nA * v:\n"; PrintVector(A*v);
    std::cout<<"\nA * 2.71:\n"; PrintMatrix(A*2.71);

    // Operatori +=, -=, *=
    std::cout<<"\nTRI IZUZETKA:\n";
    try {
        PrintMatrix(matrica += matrica2);
        std::cout<<"\n";
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintMatrix(matrica-=matrica2);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }

    try {
        PrintMatrix(matrica*=matrica2);
    } catch(std::exception &e) {
        std::cout<<e.what()<<"\n";
    }
    std::cout<<"\nA -= A:\n"; A-=A; A.Print(7);
    std::cout<<"\nB += B:\n"; B+=B; B.Print(7);
    std::cout<<"\nA *= C:\n"; A*=C; A.Print(7);
    std::cout<<"\nC *= 3:\n"; C*=3; C.Print(7);
    
    // Transponse()
    std::cout<<"\nMatrix B: \n"; B.Print(7); 
    std::cout<<"\nB transponovano:\n";
    B.Transpose(); B.Print(7);
    std::cout<<"\nPonovno transponovano B (isto kao pocetno B):\n";
    Matrix Bprim = Transpose(B); Bprim.Print(7);
    
    std::cout<<"\n***KRAJ TESTIRANJA***\n";   
    return 0;
}