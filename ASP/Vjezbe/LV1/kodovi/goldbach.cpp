#include <iostream>
#include <ctime>
#include <cmath>
#include <exception>

bool ProstBroj(int n) {
    for(int i=2; i<=sqrt(n); i++) {
        if(n%i==0) return false;
    }
    return true;
}

void Goldbach(int n, int &p, int &q) {
    p=0; q=0;
    if(n%2!=0 || n<=2) 
        throw std::logic_error("\nBroj n koji ste unijeli nije valjan!");
    
    for(int i=3; i<n; i++) {
        if(ProstBroj(i)) {
            for(int j=i; j<n; j++) {
                if(ProstBroj(j))
                    if(i+j==n) {
                        p=i;
                        q=j;
                        return;
                    }
            }
        }
    }
    if(p==0&&q==0) throw std::logic_error("\nGoldbachova hipoteza nije tačna!");
}

int main() {
    
    int n, p, q;
    flag1:
    try {
        //std::cout<<ProstBroj(11)<<std::endl;
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