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
 * @file LUDecomposer.h
 * @brief Interface klase LUDecomposer.h
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Vector.h"
#include "Matrix.h"

/**
 * @brief LUDecomposer - klasni objekat koji vrsi dekompoziciju A = LU
 * 
 * Nakon poziva konstruktora, vrsi se dekompozicija matrice na L i U.
 * Pritom se rezultati faktorizacije i podaci o obavljenim razmjenama 
 * redova cuvaju u privatnim atributima klase.
 * 
 * Nakon poziva konstruktora, metodom Solve() se mogu rjesavati sistemi 
 * linearnih jednacina u O(n^2) vremenu.
 * 
 * Podrzane su pristupne metode kojima se moze informacijama o obavljenoj
 * faktorizaciji.
*/

class LUDecomposer{
  private:
    Matrix kompaktnaLU;
    Vector permutacije;
  public:
    LUDecomposer(Matrix m);
    void Solve(const Vector &b, Vector &x) const;
    Vector Solve(Vector b) const;
    void Solve(const Matrix &b, Matrix &x) const;
    Matrix Solve(Matrix b) const;
    Matrix GetCompactLU() const;
    Matrix GetL() const;
    Matrix GetU() const;
    Vector GetPermuation() const;
};