#include <iostream>
#include <cmath>
#include <ctime>
#include <exception>

bool ProstBroj(long double n) {
    for(long double i=2; i<=sqrt(n); i++) 
        if(fmod(n,i)==0) return false;
    return true;
}

void Goldbach(long double n, long double &p, long double &q) {
    long double temp=n;
    if(n<=2 || fmod(n,2)!=0) 
        throw std::logic_error("Broj n koji ste unijeli nije valjan!");
    for(long double i=3; i<n; i++) {
        if(ProstBroj(i)) {
            temp-=i;
            if(ProstBroj(temp)) {
                p=i;
                q=temp;
                return;
            }
            else temp=n;
        }
    }
}

int main() {
    long double n, p, q;
    flag1:
    try {
        std::cout<<ProstBroj(11)<<std::endl;
        std::cout<<"Unesite broj n: "; std::cin>>n;
        clock_t vrijeme1=clock();
        Goldbach(n, p, q);
        clock_t vrijeme2=clock();
        std::cout<<std::endl<<"Goldbachovi prosti brojevi su: "<<p<<" + "<<q<<std::endl;
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        std::cout<<std::endl<<"Vrijeme izvrsenja programa je: "<<ukvrijeme<<" ms."<<std::endl;
    }
    catch(std::exception &e) {
        std::cout<<e.what();
        goto flag1;
    }

    return 0;
}
