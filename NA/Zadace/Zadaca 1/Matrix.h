#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <bits/stdc++.h>
#include "Vector.h"

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

inline Matrix::Matrix(const Vector &v){
    
    for(int i=0; i<matrica.at(0).size(); i++) {
        matrica.at(0).at(i) = v[i];
    }
}
void PrintMatrix(const Matrix &m, int width = 10, double eps = -1)
{
}

#endif