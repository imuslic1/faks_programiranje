#include "Matrix.h"
#include "Vector.h"
#include "QRDecomposer.h"

/**
 * @brief Implementacija metoda klase QRDecomposer
*/


QRDecomposer::QRDecomposer(Matrix m): R(m.NRows(), m.NCols()), diagR(m.NCols()){
    if (m.NRows() < m.NCols())
        throw std::domain_error("Invalid matrix format");

    int brKol=m.NCols(), brRed=m.NRows();
    double eps=m.GetEpsilon();

    for (int k = 0; k < brKol; k++) {
        long double norma = 0.0;
        for (int i = k; i < brRed; i++)
            norma += m[i][k] * m[i][k];

        norma = std::sqrt(norma);
        long double u=std::sqrt(norma*(norma+std::fabs(m[k][k])));
        if (u < eps)
            throw std::domain_error("Matrix is singular");
        if (m[k][k] < -std::numeric_limits<double>::epsilon())
            norma=-norma;
        m[k][k]=(m[k][k]+norma)/u;
        for (int i = k+1; i < brRed; i++)
            m[i][k]= m[i][k]/u;
        
        diagR[k]=-norma;

        for (int j = k + 1; j < brKol; j++) {
            long double s = 0.0;
            for (int i = k; i < brRed; i++)
                s += m[i][k] * m[i][j];

            for (int i = k; i < brRed; i++)
                m[i][j] -= s * m[i][k];
        }
    }
    R=m;
}

void QRDecomposer::Solve(const Vector &b, Vector &x) const{
    if (R.NRows() != R.NCols()) 
        throw std::domain_error("Matrix is not square");

    if (b.NElems() != R.NRows() || x.NElems()!=R.NRows())
        throw std::domain_error("Incompatible formats");

    x=Solve(b);
}

Vector QRDecomposer::Solve(Vector b) const{
    if (R.NRows() != R.NCols()) 
        throw std::domain_error("Matrix is not square");
        
    if (b.NElems() != R.NRows())
        throw std::domain_error("Incompatible formats");

    int brRed=R.NRows();
    Matrix r(GetR());
    Vector x(brRed);
    b=MulQTWith(b);

    for (int i = brRed - 1; i >= 0; i--) {
        long double s=b[i];
        for (int j = i + 1; j <brRed; j++)
            s-=r[i][j]*x[j];
        x[i]=s/r[i][i];  
    }
    return x;
}

void QRDecomposer::Solve(Matrix &b, Matrix &x) const{
    if (R.NRows() != R.NCols())
        throw std::domain_error("Matrix is not square");

    if (b.NRows() != R.NRows() || x.NRows()!=R.NRows() || x.NCols()!=b.NCols())
        throw std::domain_error("Incompatible formats");

    x = Solve(b);
}

Matrix QRDecomposer::Solve(Matrix b) const{
    if (R.NRows() != R.NCols())
        throw std::domain_error("Matrix is not square");

    if (b.NRows() != R.NRows())
        throw std::domain_error("Incompatible formats");

    int brRed=b.NRows(), brKol=b.NCols();
    Matrix rez(brRed, brKol);

    for (int j = 0; j < brKol; j++) {
        Vector kolonaB(brRed);
        for (int i = 0; i < brRed; i++)
            kolonaB[i] = b[i][j];

        Solve(kolonaB, kolonaB);
        for (int i = 0; i < brRed; i++)
            rez[i][j] = kolonaB[i];
    }
    return rez;
}

Vector QRDecomposer::MulQWith(Vector v) const{
    if (v.NElems() != R.NRows())
        throw std::domain_error("Incompatible formats");
    
    int brRed=R.NRows();
    for (int k = brRed-1; k >=0; k--) {
        long double skalarniProizvod = 0.0;
        for (int i = k; i < brRed; i++) 
            skalarniProizvod += R[i][k] * v[i];

        for (int i = k; i < brRed; i++) 
            v[i] -= skalarniProizvod * R[i][k];
    }
    return v;
}

Matrix QRDecomposer::MulQWith(Matrix m) const{
    if (m.NRows() != R.NRows())
        throw std::domain_error("Incompatible formats");

    int brKolM=m.NCols(), brRedM=m.NRows();
    for (int j = 0; j < brKolM; j++) {
        Vector kolonaM(brRedM);

        for (int i = 0; i < brRedM; i++)
            kolonaM[i] = m[i][j];

        kolonaM = MulQWith(kolonaM);

        for (int i = 0; i < brRedM; i++) {
            m[i][j] = kolonaM[i];
        }
    }
    return m;
}

Vector QRDecomposer::MulQTWith(Vector v) const{
    if (v.NElems() != R.NRows())
        throw std::domain_error("Incompatible formats");

    int brRed=R.NRows();
    for (int k = 0; k <brRed ; k++) {
        long double skalarniProizvod = 0.0;

        for (int i = k; i < brRed; i++)
            skalarniProizvod += R[i][k] * v[i];

        for (int i = k; i < brRed; i++) 
            v[i] -= skalarniProizvod * R[i][k];
    }
    return v;
}

Matrix QRDecomposer::MulQTWith(Matrix m) const{
    if (m.NRows() != R.NRows())
        throw std::domain_error("Incompatible formats");

    int brKolM=m.NCols(), brRedM=m.NRows();
    for (int j = 0; j < brKolM; j++) {
        Vector kolonaM(brRedM);

        for (int i = 0; i < brRedM; i++)
            kolonaM[i] = m[i][j];

        kolonaM = MulQTWith(kolonaM);

        for (int i = 0; i <brRedM; i++)
            m[i][j] = kolonaM[i];
    }
    return m;
}

Matrix QRDecomposer::GetQ() const{
    int brRed=R.NRows(), brKol=R.NCols();
    Matrix q(brRed, brRed);
    for(int j=0; j<brRed; j++){
        for(int i=0; i<brRed; i++)
            q[i][j]=0;
        q[j][j]=1.0;
        for(int k=brKol-1; k>=0; k--){
            long double s=0.0;
            for(int i=k; i<brRed; i++)
                s+=R[i][k]*q[i][j];
            for(int i=k; i<brRed; i++)
                q[i][j]-=s*R[i][k];
        }
    }
    return q;
}

Matrix QRDecomposer::GetR() const{
    int brRed = R.NRows(), brKol=R.NCols();
    Matrix R_vracanje(brRed, brKol);
    for (int j = 0; j < brKol; j++) {
        for (int i = 0; i < j; i++) {
            R_vracanje[i][j] = R[i][j];
        }
        R_vracanje[j][j]=diagR[j];
    }
    return R_vracanje;
}
