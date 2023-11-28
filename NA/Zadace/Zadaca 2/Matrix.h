/**
 * Univerzitet u Sarajevu 
 * Elektrotehnicki fakultet Sarajevo
 * Odsjek za Racunarstvo i informatiku
 * 
 * Numerički Algoritmi
 * Ismar Muslic, 19304
 * 
 * Implementacija raznih funkcija 
 * za rjesavanje problema linearne algebre
 * 
*/

/**
 * @file Matrix.h
 * @brief Interface klase Matrix
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Vector.h"

/**
 * @brief Standardna matrica realnih brojeva organizirana kao std::vector<std::vector<double>>
 * 
 * Objekat ove klase podrzava sve standardne 
 * aritmeticke operacije nad matricama, kao i 
 * matricno lijevo dijeljenje. 
 * 
 * Moguce je saznati rang, transponovati matricu
 * ili naci joj inverznu i slicno.
 * 
 * Indeksacija elemenata se vrsi pomocu [i][j] ili (i, j), 
 * pritom (i, j) krece sa indeksacijom od 1, a ne od 0.
 * (i, j) takodjer vodi racuna o validnosti indeksa, dok
 * [i][j] ne vodi.
 * 
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
    void Chop(double eps = -1);
    bool EqualTo(const Matrix &m, double eps = -1) const;
    friend Matrix LeftDiv(Matrix m1, Matrix m2);
    friend Vector LeftDiv(Matrix m, Vector v);
    friend Matrix operator /(const Matrix &m, double s);
    Matrix &operator /=(double s);
    friend Matrix operator /(Matrix m1, Matrix m2);
    Matrix &operator /=(Matrix m);
    double Det() const;
    friend double Det(Matrix m);
    void Invert();
    friend Matrix Inverse(Matrix m);
    void ReduceToRREF();
    friend Matrix RREF(Matrix m);
    int Rank() const;
    friend int Rank(Matrix m);
};