#include <bits/stdc++.h>
#include "Vector.h"

double VectorNorm(const Vector &v) {
    long double sumakv = 0;
    for(auto a : v.v) sumakv+=a;
    return sqrt(sumakv);
}

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
        a(0) = 5;
        std::cout<<a(0)<<"   "<<a(10);
        //testiranje kraj
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    return 0;
}