#include <iostream>
#include <ctime>

int main() {

    long double s=0; int n;
    clock_t vrijeme1 = clock();
    for(int i=0; i<n; i++) 
        for(int j=0; j<n; j++)
            if(i==j)
                for(int k=0; k<n*n; k++)
                    s++;
    clock_t vrijeme2 = clock();

    double ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout<<"Program izvršen za "<<s<<" iteracija"<<std::endl;
    std::cout<<"Vrijeme izvršavanja: "<<ukvrijeme<<" ms.\n";
    return 0;
}
