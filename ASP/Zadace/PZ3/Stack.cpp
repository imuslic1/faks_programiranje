#include "Stek.h"
#include <bits/stdc++.h>

int main() {
    try {
        Stek<int> s;
        
        for(int i=1; i<=33000; ++i)
            s.stavi(i);
        std::cout<<"\nVRH: "<<s.vrh();
        std::cout<<"\nBROJ ELEMENATA: "<<s.brojElemenata();
        for(int i=0; i<10000; ++i)
            s.skini();
        std::cout<<"\nSKINUTO 10000 ELEMENATA!";
        std::cout<<"\nVRH: "<<s.vrh();
        s.brisi();
        std::cout<<"\nSTACK OBRISAN!";
        std::cout<<"\nBROJ ELEMENATA: "<<s.brojElemenata();
    } catch (std::exception &e) {
        std::cout<<"\nHandled exception: "<<e.what()<<"\n";
    }

    Stek<std::vector<int>> s;

    return 0;
}
