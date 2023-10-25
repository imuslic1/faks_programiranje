#include <bits/stdc++.h>
#include "Matrix.h"
#include "Vector.h"
/*
double VectorNorm(const Vector &v) {
    long double sumakv = 0;
    for(auto a : v.v) sumakv+=a;
    return sqrt(sumakv);
}*/

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
        std::cout<<"\n***TEST1: A+=B***\n"; a+=b;
        a.Print(); std::cout<<"\n"; b.Print(); std::cout<<"\n***TEST2: operator*(3, a)\n";
        a=operator*(3, a);
        a.Print(); std::cout<<"\nTEST3: B*=3\n";
        b*=3; b.Print();
        std::cout<<"\n***TEST4: 0DIV EXCEPT:***\n";
        //operator/(0, b);

        Matrix matrica(2, 3);

        getchar();
        //testiranje kraj
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    return 0;
}