#include "Red.h"
#include <iostream>

int main() {
    int brel;
Red<int> r;
for (int i(1); i<=5; i++)
	r.stavi(i);
{
        // Konstruktor kopije
	Red<int> r2(r);
	Red<int> r3;
        // Operator dodjele
	(r3=r).brojElemenata();
        // Destruktivna samododjela
        (r=r).brojElemenata();

	r.skini();
	brel = r2.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r2.skini() << " ";
	brel = r3.brojElemenata();
	for (int i(0); i<brel; i++)
		std::cout << r3.skini() << " ";
}
brel = r.brojElemenata();
for (int i(0); i<brel; i++)
	std::cout << r.skini() << " ";



    return 0;
}
