#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;


int f1(int n, int s) {
    for(int i=0; i<n; i++) s++;             //O(n)
    return n;
}

int f2(int n, int s) {
    for(int i=0; i<=n*n; i++) s++;          //O(n^2)
    return s;
}

int f3(int n, int s) {
    for(int i=1; i<n; i*=2) s++;            //O(log n)
    return s;
}

int f4(int n, int s) {
    for(int i=0; i<n*n*n; i++) s++;         //O(n^3)
    return n;
}

int main() {

    int t,n; cin>>t>>n;
    f1(t,0) + f2(t,0) + f3(t,0) + f4(t,0);  //Ukupna kompleksnost O(n^3)
                                            //jer je ona najveća

    f1(n,0) * f2(n,0) + f3(t,0);            //Ukupna kompleksnost O(n^2)

    f1(f1(t,0),0);                          //Ukupna kompleksnost O(n)
                                            //jer se poziva 2x zaredom

    f2(f2(t,0),0);                          //Ukupna kompleksnost O(n^2)

    for(int i=0; i<n; i++) {                //Ukupno O(n^4)
        if(f1(n, 0)%2==0) f4(n,0);
        else f1(n,0);
    }

    t=8;
    for(int i=0; i<n; i++) {                //O(n), nema veze sa t
        t=t*t;
    }
    for(int i=0; i<t; i++) {                //O(n), nema veze sa n
        n++;
    }

                                            //Ukupno O(n+n) = O(n)

    return 0;
}