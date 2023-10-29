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
    std::cout<<"***TEST1: std::Vector***\n\n";
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
    
    //std::cout<<"\n***TEST4: 0DIV EXCEPT:***\n";
    //operator/(0, b);
/*
    Matrix matrica(2, 3);
    //Matrix matrica2 = {{1, 2}, {1, 2, 3}}; //test sekvencijalnog konstruktora
    //std::cout<<"***debug 001: vracanje reda matrice***\n";
    int foo = matrica.NCols();
    for(double* i = matrica[1]; i<matrica[1]+foo; i++)
        std::cout<<*i;
    std::cout<<"\n"<<matrica.Norm()<<"\n";
    matrica.Print();
    std::cout<<"\nMNOZENJE MATRICE VEKTOROM: \n";
    Vector v = {1, 2, 3};
    Matrix A = {{1, 2, 3}, {2, 1, 1}, {4, 3, 2}};
    Matrix B = {{1, 2}, {3, 6}, {7, 9}, {5, 2}};
    auto rezultat_mnozenja = A*v;
    rezultat_mnozenja.Print();
    getchar();
    std::cout<<"\nTRANSPONUJ A: \n";
    A.Transpose(); A.Print();
    std::cout<<"\n";
    Matrix C = Transpose(A); C.Print();
    C*=3; C.Print();
    std::cout<<"\nTRANSPONUJ B: \n";
    //B.Transpose(); B.Print();
    //Transpose(B); B.Print();

*/

    return 0;
}