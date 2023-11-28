#include "Matrix.h"
#include "Vector.h"
#include "LUDecomposer.h"

/**
 * @brief Implementacija metoda klase LUDecomposer
*/

LUDecomposer::LUDecomposer(Matrix m) : kompaktnaLU(m.NRows(),m.NCols()), permutacije(m.NRows()){
    if(m.NRows()!=m.NCols())
        throw std::domain_error("Matrix is not square");
    int brRedM=m.NRows(), brKol=m.NCols();
    double eps=m.GetEpsilon();

    for(int j=0; j<brRedM; j++){
        for(int i=0; i<=j; i++){
            long double s=m[i][j];
            for(int k=0; k<i; k++)
                s-=m[i][k]*m[k][j];
            m[i][j]=s;
        }
        int p=j;
        for(int i=j+1; i<brRedM; i++){
            long double s=m[i][j];
            for(int k=0; k<j; k++)
                s-=m[i][k]*m[k][j];
            m[i][j]=s;
            if(std::fabs(s)>std::fabs(m[p][j])) p=i;
        }
        if(std::fabs(m[p][j])<eps)
            throw std::domain_error("Matrix is singular");
        if(p!=j)
            for(int l=0; l<brKol; l++){
                double temp=m[j][l];
                m[j][l]=m[p][l];
                m[p][l]=temp;
            }
        permutacije[j]=p;
        long double u=m[j][j];
        for(int i=j+1; i<brRedM; i++)
            m[i][j]/=u;
    }
    kompaktnaLU=m;
}

void LUDecomposer::Solve(const Vector &b, Vector &x) const{
    if (b.NElems() != kompaktnaLU.NRows() || x.NElems() != kompaktnaLU.NRows())
        throw std::domain_error("Incompatible formats");

    x=Solve(b);
}

Vector LUDecomposer::Solve(Vector b) const{
    if (b.NElems() != kompaktnaLU.NRows())
        throw std::domain_error("Incompatible formats");

    int vel= b.NElems();
    Vector y(vel), x(vel);
    Matrix l(GetL()), u(GetU());

    // Ly = Pb
    for (int i = 0; i < vel; i++) {
        int p=permutacije[i];
        long double s=b[p];
        b[p]=b[i];
        for (int j = 0; j < i; j++) {
            s-= l[i][j] * y[j];
        }
        y[i]=s;
    }

    // Ux = y
    for (int i = vel - 1; i >= 0; i--) {
        long double s=y[i];
        for (int j = i + 1; j < vel; j++) {
            s -= u[i][j] * x[j];
        }
        x[i]= s/u[i][i];
    }
    return x;
}

void LUDecomposer::Solve(const Matrix &b, Matrix &x) const{
    if (b.NRows() != kompaktnaLU.NRows() || b.NCols() != x.NCols() 
        || b.NRows() != x.NRows())
        throw std::domain_error("Incompatible formats");
    x=Solve(b);
}

Matrix LUDecomposer::Solve(Matrix b) const{
    if (b.NRows() != kompaktnaLU.NRows())
        throw std::domain_error("Incompatible formats");

    int brRed = b.NRows();
    int brKol = b.NCols();
    Matrix rez(brRed, brKol);
    // Rješavanje za svaku kolonu matrice B
    for (int kol = 0; kol < brKol; kol++) {
        Vector bKol(brRed);
        for (int red = 0; red < brRed; red++)
            bKol[red] = b[red][kol];
        Solve(bKol, bKol);

        for (int red = 0; red <brRed; red++)
            rez[red][kol] = bKol[red];
    }
    return rez;
}
    
Matrix LUDecomposer::GetCompactLU() const{
    return kompaktnaLU;
}

Matrix LUDecomposer::GetL() const{
    int brRed = kompaktnaLU.NRows();
    Matrix L(brRed, brRed);
    for (int i = 0; i < brRed; i++) {
        L[i][i] = 1.0;
        for (int j = 0; j < i; j++) {
            L[i][j] = kompaktnaLU[i][j];
        }
    }
    return L;
}

Matrix LUDecomposer::GetU() const{
    int brRed = kompaktnaLU.NRows();
    Matrix U(brRed, brRed);
    for (int i = 0; i < brRed; i++)
        for (int j = i; j < brRed; j++)
            U[i][j] = kompaktnaLU[i][j];
    return U;
}

Vector LUDecomposer::GetPermuation() const{
    int vel=permutacije.NElems();
    Vector p(permutacije);
    for(int i=0; i<vel; i++)
        p[i]++;
    return p;
}