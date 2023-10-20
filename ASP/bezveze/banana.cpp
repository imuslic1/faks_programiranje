#include <iostream>
#include <ctime>

int main() {
    long double s=0, n;
    std::cin>>n;
    /*for(int i=1; i<n; i++){
		for(int j=i; j<n; j*=2){
            s++; std::cout<<"vrtim"<<std::endl;
        }
    }*/
	clock_t vrijeme1 = clock();
	for(int i=0; i<n*n*n; i++) 
		for(int j=0; j<n*n; j++) 
			if(i>n && j<n)
				for(int k=0; k<n*n*n*n; k++)
					s++;
    clock_t vrijeme2 = clock();
	int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout<<"Program ima: "<<s<<" iteracija.\n";
	std::cout<<"Vrijeme izvršavanja: "<<ukvrijeme<<" ms.\n";
    return 0;
}