#include "Matrix.h"
#include "Vector.h"

/**
 * @brief Implementacija metoda klase Matrix.h
*/

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
    for(auto i:matrica)
        for(auto j:i)
            sumakv+=j*j;
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
    m.Print(width, eps);
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

inline void Matrix::Chop(double eps) {
    if(eps<0) eps = this->GetEpsilon();
    for(auto a:matrica)
        for(auto b:a)
            if(std::fabs(b) < eps) b=0;
}

inline bool Matrix::EqualTo(const Matrix &m, double eps) const {
    int brRedova = this->NRows(), brKolona = this->NCols();
    if(brRedova != m.NRows() || brKolona != m.NCols()) return false;
    if(eps < 0) eps = this->GetEpsilon();
    for(int i=0; i<brRedova; i++)
        for(int j=0; j<brKolona; j++)
            if(std::fabs(this->matrica[i][j] - m[i][j] > eps))
                return false;
    return true;
}

Matrix LeftDiv(Matrix m1, Matrix m2) {
    if(m1.NCols()!=m1.NRows()) 
        throw std::domain_error("Divisor matrix is not square");
    if(m1.NRows()!=m2.NRows())
        throw std::domain_error("Incompatible formats");
    int brRedova1=m1.NRows(), brKolona2=m2.NCols(), brKolona1=m1.NCols();
    double eps=m1.GetEpsilon();

    for(int k=0; k<brKolona1; k++){
        int p=k;
        for(int i=k+1; i<brRedova1; i++){
            if(std::fabs(m1[i][k])>std::fabs(m1[p][k]))
                p=i;
        }
        if(std::fabs(m1[p][k])<eps)
            throw std::domain_error("Divisor matrix is singular");
        if(p!=k){
            std::swap(m1.matrica[k], m1.matrica[p]);
            std::swap(m2.matrica[k], m2.matrica[p]);
        }
        for(int i=k+1; i<brKolona1; i++){
            long double u=m1[i][k]/m1[k][k];
            for(int j=k+1; j<brKolona1; j++)
                m1[i][j]-=u*m1[k][j];
            for(int j=0; j<brKolona2; j++)
                m2[i][j]-=u*m2[k][j];
        }
    }
    //supstitucija unazad
    Matrix rez(brRedova1, brKolona2);
    for(int k=0; k<brKolona2; k++){
        for(int i=brRedova1-1; i>=0; i--){
            long double s=m2[i][k];
            for(int j=i+1; j<brRedova1; j++)
                s=s-m1[i][j]*rez[j][k];
            rez[i][k]=s/m1[i][i];
        }
    }
    return rez;
}

Vector LeftDiv(Matrix m, Vector v){
    if(m.NCols()!=m.NRows()) 
        throw std::domain_error("Divisor matrix is not square");
    if(m.NRows()!=v.NElems())
        throw std::domain_error("Incompatible formats");
    int velM=m.NRows();
    double eps=m.GetEpsilon();

    for(int k=0; k<velM; k++){
        int p=k;
        for(int i=k+1; i<velM; i++){
            if(std::fabs(m[i][k])>std::fabs(m[p][k]))
                p=i;
        }
        if(std::fabs(m[p][k])<eps)
            throw std::domain_error("Divisor matrix is singular");
        if(p!=k){
            std::swap(m.matrica[k], m.matrica[p]);
            std::swap(v[k], v[p]);
        }
        for(int i=k+1; i<velM; i++){
            long double u=m[i][k]/m[k][k];
            for(int j=k+1; j<velM; j++)
                m[i][j]-=u*m[k][j];
            v[i]-=u*v[k];
        }
    }
    //supstitucija unazad
    Vector rez(velM);
    for(int i=velM-1; i>=0; i--){
        long double s=v[i];
        for(int j=i+1; j<velM; j++)
            s-=m[i][j]*rez[j];
        rez[i]=s/m[i][i];
    }
    return rez;
}

Matrix operator /(const Matrix &m, double s){
    Matrix rez=m;
    try{
        return rez/=s;
    }
    catch(std::domain_error &e){
        throw e;
    }
}

Matrix & Matrix::operator /=(double s){
    if(std::fabs(s-0)<std::numeric_limits<double>::epsilon()) 
        throw std::domain_error("Division by zero");
    int brRed=this->NRows(), brKol=this->NCols();
    for(int i=0; i<brRed; i++)
        for(int j=0; j<brKol; j++)
            this->matrica[i][j]/=s;
    return *this;
}

Matrix operator /(Matrix m1, Matrix m2){
    try{
        return m1/=m2;
    }
    catch(std::domain_error &e){
        throw e;
    }
}

Matrix & Matrix::operator /=(Matrix m){
    if(m.NCols()!=m.NRows()) 
        throw std::domain_error("Divisor matrix is not square");
    if(this->NCols()!=m.NRows())
        throw std::domain_error("Incompatible formats");
    int velM1=m.NRows(), brRedM2=this->NRows(), brKolM1=m.NCols();
    double eps=this->GetEpsilon();

    for(int k=0; k<velM1; k++){
        int p=k;
        for(int i=k+1; i<velM1; i++){
            if(std::fabs(m[i][k])>std::fabs(m[p][k]))
                p=i;
        }
        if(std::fabs(m[p][k])<eps)
            throw std::domain_error("Divisor matrix is singular");
        if(p!=k){
            for (int i = 0; i < velM1; i++) {
                std::swap(m[i][k], m[i][p]);
            }
            for (int i = 0; i < brRedM2; i++) {
                std::swap((*this)[i][k], (*this)[i][p]);
            }
        }
        for(int i=k+1; i<brKolM1; i++){
            long double u=m[k][i]/m[k][k];
            for(int j=k+1; j<velM1; j++)
                m[j][i]-=u*m[j][k]; 
            for(int j=0; j<brRedM2; j++)
                (*this)[j][i]-=u*(*this)[j][k];
        }
    }
    //supstitucija unazad
    Matrix rez(brRedM2, velM1);
    for (int k = 0; k < brRedM2; k++) {
        for (int i = brKolM1 - 1; i >= 0; i--) {
            long double s=(*this)[k][i];
            for (int j = i + 1; j < velM1; j++) {
                s-=m[j][i] * rez[k][j];
            }
            rez[k][i]=s/ m[i][i];
        }
    }
    *this=rez;
    return *this;
}

double Matrix::Det() const{
    if(this->NRows()!=this->NCols())
        throw std::domain_error("Matrix is not square");
    long double det=1;
    int brRed=this->NRows();
    double eps=this->GetEpsilon();
    Matrix pomocna=(*this);

    for(int k=0; k<brRed; k++){
        int p=k;
        for(int i=k+1; i<brRed; i++){
            if(std::fabs(pomocna[i][k])>std::fabs(pomocna[p][k]))
                p=i;
        }
        if(std::fabs(pomocna[p][k])<eps)
            return 0;
        if(p!=k){
            std::swap(pomocna.matrica[k],pomocna.matrica[p]);
            det*=-1;
        }
        det=det*pomocna[k][k];
        for(int i=k+1; i<brRed; i++){
            long double u=pomocna[i][k]/pomocna[k][k];
            for(int j=k+1; j<brRed; j++)
                pomocna[i][j]-=u*pomocna[k][j];
        }
    }
    return det;
}

double Det(Matrix m){
    if(m.NRows()!=m.NCols())
        throw std::domain_error("Matrix is not square");
    try{
        return m.Det();
    }
    catch(std::domain_error &e){
        throw e;
    }
}

void Matrix::Invert(){
    if(this->NRows()!=this->NCols())
        throw std::domain_error("Matrix is not square");
    int brRed=this->NRows();
    double eps=this->GetEpsilon();
    std::vector<int> pivot(brRed);

    for(int k=0; k<brRed; k++){
        int p=k;
        for(int i=k+1; i<brRed; i++){
            if(std::fabs(matrica[i][k])>std::fabs(matrica[p][k]))
                p=i;
        }
        if(std::fabs(matrica[p][k])<eps)
            throw std::domain_error("Matrix is singular");
        if(p!=k){
            std::swap(matrica[k],matrica[p]);
        }
        pivot[k]=p;
        long double u=matrica[k][k];
        matrica[k][k]=1.0;
        for(int j=0; j<brRed; j++)
            matrica[k][j]/=u;
        for(int i=0; i<brRed; i++){
            if(i!=k){
                u=matrica[i][k];
                matrica[i][k]=0.0;
                for(int j=0; j<brRed; j++)
                    matrica[i][j]-=u*matrica[k][j];
            }
        }
    }
    for(int j=brRed-1; j>=0; j--){
        int p=pivot[j];
        if(p!=j){
            for(int i=0; i<brRed; i++){
                std::swap(matrica[i][j], matrica[i][p]);
            }
        }
    }
    
}

Matrix Inverse(Matrix m){
    if(m.NRows()!=m.NCols())
        throw std::domain_error("Matrix is not square");
    try{
        m.Invert();
        return m;
    }
    catch(std::domain_error &e){
        throw e;
    }
}

void Matrix::ReduceToRREF(){
    int k=-1, l=-1, brRed=this->NRows(), brKol=this->NCols();
    std::vector<bool> w(brKol, false);
    double eps=this->GetEpsilon();

    while(k<brRed && l<brKol){
        l++; k++;
        double v=0;
        int p=0;
        while(v<eps && l<brKol){
            p=k;
            for(int i=k; i<brRed; i++){
                if(std::fabs(matrica[i][l])>v){
                    v=std::fabs(matrica[i][l]);
                    p=i;
                }
            }
            if(v<eps) l++;
        }
        if(l<brKol){
            w[l]=true;
            if(p!=k) std::swap(matrica[p], matrica[k]);
            long double u=matrica[k][l];
            for(int j=l; j<brKol; j++)
                matrica[k][j]/=u;
            for(int i=0; i<brRed; i++){
                if(i!=k){
                    u=matrica[i][l];
                    for(int j=l; j<brKol; j++)
                        matrica[i][j]-=u*matrica[k][j];
                }
            }
        }
    }
}

Matrix RREF(Matrix m){
    m.ReduceToRREF();
    return m;
}

int Matrix::Rank() const{
    Matrix pomocna=*this;
    pomocna.ReduceToRREF();
    int rank = 0, brRed=this->NRows(), brKol=this->NCols();
    double eps=this->GetEpsilon();

    for (int i=0; i<brRed; i++) {
        int j=i;
        while(j<brKol && pomocna[i][j]<std::numeric_limits<double>::epsilon()) 
            j++;
        if(j==brKol) break;
        ++rank;
    }
    return rank;
}

int Rank(Matrix m){
    return m.Rank();
}