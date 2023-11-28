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
 * @file QRDecomposer.h
 * @brief Interface klase QRDecomposer.h
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
 * @brief QRDecomposer - klasni objekat koji vrsi dekompoziciju A = QR
 * 
 * Konstruktor klase vrsi nepotpunu QR faktorizaciju proslijedjene matrice
 * koristeci Householder algoritam. Faktorizacija je nepotpuna, jer se ne 
 * formira matrica Q eksplicitno, vec se cuvaju odgovarajuci vektori potrebni 
 * za formiranje Householderovih matrica. Sve informacije o obavljenoj 
 * faktorizaciji cuvaju se u privatnim atributima klase.
 * 
 * Nakon poziva konstruktora, metodom Solve() se mogu rjesavati sistemi 
 * linearnih jednacina u O(n^2) vremenu. Solve() metode rade samo ukoliko je
 * faktorizirana matrica bila kvadratna.
*/

class QRDecomposer{
   private:
    Matrix R;
    Vector diagR;
   public:
    QRDecomposer(Matrix m);
    void Solve(const Vector &b, Vector &x) const;
    Vector Solve(Vector b) const;
    void Solve(Matrix &b, Matrix &x) const;
    Matrix Solve(Matrix b) const;
    Vector MulQWith(Vector v) const;
    Matrix MulQWith(Matrix m) const;
    Vector MulQTWith(Vector v) const;
    Matrix MulQTWith(Matrix m) const;
    Matrix GetQ() const;
    Matrix GetR() const;
};