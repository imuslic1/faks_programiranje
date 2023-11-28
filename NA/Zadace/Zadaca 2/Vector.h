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
 * @file Vector.h
 * @brief Interface klase Vector
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>


/**
 * @brief Vector realnih brojeva, omotač oko bibliotečkog std::vector<double>
 * 
 * Objekat tipa Vector se implementira i koristi kao klasicna vektor-kolona
 * iz linearne algebre. Specijaliziran je za tip elemenata double, te podrzava
 * sve aritmeticke operacije koje bi se mogle izvrsiti nad vektor-kolonom.
 * 
 * Za ispis se koristi metoda Print(), dok se indeksacija moze vrsiti pomocu 
 * [i][j] ili (i, j), pri cemu (i, j) krece sa indeksacijom od 1, a ne od 0.
 * (i, j) takodjer vodi racuna o validnosti indeksa, dok [i][j] ne vodi.
 * 
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
    void Print(char separator = '\n', double eps = -1) const;
    friend void PrintVector(const Vector &v, char separator = '\n', double eps = -1) {
        if(eps<=0) eps = v.GetEpsilon();
        for(int i=0; i<v.v.size(); i++) {
            double trenutni = v.v.at(i);
            if(fabs(trenutni)<eps) trenutni = 0;
            if(i==v.v.size()-1 && separator != '\n') std::cout<<trenutni;
            else std::cout<<trenutni<<separator;
        }
    }
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
    void Chop(double eps = 1);
    bool EqualTo(const Vector &v, double eps = -1) const;
};