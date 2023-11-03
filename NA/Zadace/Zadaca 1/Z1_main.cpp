#include <bits/stdc++.h>
#include "Matrix.h"
#include "Vector.h"

/**
 * Numericki Algoritmi - Zadaca 1
 *    Main funkcija - aplikativni testovi
*/


int main() {

    /**
     * Aplikativni testovi: class Vector
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
    std::cout<<"\nc = a*a1: \n"; std::cout<<a*a1;
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
    
    // Konstruktori, vraćanje reda matrice, funkcija NCols()
    std::cout<<"***TEST2: Matrix***\n\n";
    Matrix matrica(2, 3);
    matrica = {{3.14, 2.71, 9.81}, {7.21, 2.20, 57.2958}};
    std::cout<<"\nIZUZETAK:\n";
    try {
        Matrix matrica2 = {{1, 2}, {1, 2, 3}}; // Grbava matrica, izuzetak
        } catch(std::exception &e) {
            std::cout<<e.what()<<"\n";
        } 
    std::cout<<"\nMatrix A:\n"; matrica.Print();
    std::cout<<"\nPrvi red Mat A: \n";
    int foo = matrica.NCols();
    for(double* i = matrica[1]; i<matrica[1]+foo; i++)
        std::cout<<*i;
    
    // Norm(), mnozenja
    std::cout<<"\nNorma Matrice A: "<<matrica.Norm()<<"\n";
    std::cout<<"\nMNOZENJE MATRICE VEKTOROM: \n";
    std::cout<<"\nVector v:\n"; 
    Vector v = {1.1, 2.2, 3.3}; v.Print();
    Matrix A = {{1.11, 2.22, 3.33}, {2.33, 1.22, 1.11}, {4.33, 3.22, 2.11}};
    Matrix B = {{1.99, 2.47}, {3.32, 6.64}, {7.88, 9.66}, {5.755, 2.666}};
    auto rezultat_mnozenja = A*v; rezultat_mnozenja.Print();

    // Transponovanje A, Mnozenje skalarom, 
    // Mnozenje dvije matrice(izuzetak)
    std::cout<<"\nA transponovano:\n";
    A.Transpose(); A.Print();
    Matrix C = Transpose(A); C.Print();
    C*=3; C.Print();
    std::cout<<"\nIZUZETAK: \n";
    try {
        PrintMatrix(A*B);
        } catch(std::exception &e) {
            std::cout<<e.what()<<"\n";
    }
    std::cout<<"\n***KRAJ TESTIRANJA***\n";
    return 0;
}