#include <bits/stdc++.h>
#include "Vector.h"
/*
double VectorNorm(const Vector &v) {
    long double sumakv = 0;
    for(auto a : v.v) sumakv+=a;
    return sqrt(sumakv);
}*/

class Matrica {
    std::vector<std::vector<int>> matrica;
public:
    explicit Matrica(int m, int n) {
        this->matrica = std::vector<std::vector<int>> (m, std::vector<int>(n));
    }   

};

int main() {
    try {
        //testiranje ovdje:
        Vector a(3);
        Vector b(3);
        for(int i=0; i<3; i++) {
            double x; std::cin>>x;
            a[i]=x;
            b[i]=x;
        }
        std::cout<<"\n"; a+=b;
        a.Print(); std::cout<<"\n"; b.Print(); std::cout<<"\n";
        a=operator*(3, a);
        a.Print();
        //testiranje kraj
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    return 0;
}