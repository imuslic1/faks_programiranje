#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
void bubble_sort(T* niz, int vel) {
    for(int i=vel-1; i>=1; --i) {
        for(int j=1; j<=i; ++j) {
            if(niz[j-1] > niz[j]) {
                T temp = niz[j-1];
                niz[j-1] = niz[j];
                niz[j] = temp;
            }
        }
    }
}

template <typename T> 
void selection_sort(T* niz, int vel) {
    for(int i=0; i<=vel-2; ++i) {
        T min = niz[i];
        int pmin = i;
        for(int j=i+1; j<=vel-1; ++j) {
            if(niz[j]<min) {
                min = niz[j];
                pmin = j;
            }
        }
        niz[pmin] = niz[i];
        niz[i] = min;
    }
}

template <typename T>
void zamijeni(T* niz, int i, int j) {
    T temp = niz[i];
    niz[i] = niz[j];
    niz[j] = temp;
}

template <typename T>
int particija(T* niz, const int first, const int last){
    T pivot = niz[first];
    int p = first + 1;
    while(p<=last) {
        if(niz[p] <= pivot)
            ++p;
        else break;
    }
    for(int i=p+1; i<=last; ++i) {
        if(niz[i]<pivot) {
            zamijeni(niz, p, i);
            ++p;
        }    
    }
    zamijeni(niz, first, p-1);
    return p-1;

}

template <typename T>
void quickSort(T* niz, const int prvi, const int zadnji) {
    if(prvi<zadnji) {
        int j = particija(niz, prvi, zadnji);
        quickSort(niz, prvi, j-1);
        quickSort(niz, j+1, zadnji);
    }

}

template <typename T>
void quick_sort(T* niz, int vel) {
    quickSort(niz, 0, vel-1);
}

template <typename T>
void merge(T* niz, const int l, const int p, const int q, const int u) {
    int i = 0, j = q-l, k = l;
    T *B = new T[u-l+1];
    for(int m=0; m<=u-l; ++m) 
        B[m] = niz[l+m];
    while(i<=p-l && j<=u-l) {
        if(B[i] < B[j])
            niz[k] = B[i++];
        else 
            niz[k] = B[j++];
        ++k;
    }
    while(i<=p-l)
        niz[k++] = B[i++];
    while(j<=u-l)
        niz[k++] = B[j++];
    delete[] B; 
}

template <typename T>
void mergeSort(T* niz, int l, int u) {
   if(u>l) {
        int p = (l+u-1) / 2;
        int q = p+1;
        mergeSort(niz, l, p);
        mergeSort(niz, q, u);
        merge(niz, l, p, q, u);
    }
}

template <typename T>
void merge_sort(T* niz, int vel) {
    mergeSort(niz, 0, vel-1);    
}

void ucitaj(std::string filename, int*& niz, int &vel) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Greska pri otvaranju datoteke!");
        return;
    }

    // Count the number of integers in the file
    vel = 0;
    int num;
    while (file >> num) {
        vel++;
    }

    // Allocate memory for the array
    niz = new int[vel];

    // Reset file and read integers into the array
    file.clear();
    file.seekg(0, std::ios::beg);
    for (int i = 0; i < vel; ++i) {
        file >> niz[i];
    }

    file.close();
}

void generisi(std::string filename, int vel) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Greska pri otvaranju datoteke!");
        return;
    }

    // Seed the random number generator
    std::srand(std::time(0));

    // Generate and write random integers to the file
    for (int i = 0; i < vel; ++i) {
        file << std::rand() % 1000 << " "; // Modify the range as needed
    }

    file.close();
}

template <typename T>
bool check_state(T* niz, int vel) {
    for(int i=1; i<vel; ++i)
        if(niz[i]<niz[i-1])
            return false;
    return true;
}

template <typename T>
void write_to_file(std::string filename, T* niz, int vel) {
    std::ofstream ispis(filename);
        for(int i=0; i<vel; ++i)
            ispis<<niz[i]<<" ";
        ispis.close();
}

int init() {
    int *niz;
    int vel;
    std::cout<<"Zeljena velicina niza (0 za Izlaz): "; std::cin>>vel;
    if(vel==0) return 1;
    try {
        generisi("brojevi.txt", vel);
    } catch(std::ios_base::failure &f) {
        std::cout<<f.what();
        return -1;
    }
    std::cout<<"\nDatoteka uspjesno generisana!";
    try {
        ucitaj("brojevi.txt", niz, vel);
    } catch(std::ios_base::failure &f) {
        std::cout<<f.what();
        return -1;
    }
    std::cout<<"\nDatoteka uspjesno ucitana u program. Niz kreiran.";
    std::cout<<"\nOdaberite zeljeni algoritam sortiranja: \n\n";

    std::cout << std::setw(20) << std::left << "Bubble Sort" << "[1]\n";
    std::cout << std::setw(20) << std::left << "Selection Sort" << "[2]\n";
    std::cout << std::setw(20) << std::left << "QuickSort" << "[3]\n";
    std::cout << std::setw(20) << std::left << "Merge Sort" << "[4]\n";
    std::cout << std::setw(20) << std::left << "Izlaz" << "[0]\n\n";
    std::cout << "Odabir: ";

    int choice; std::cin>>choice;
    clock_t start, end;
    choice:
    switch(choice) {
        case 0:
            return 1;
        case 1: 
            start = clock();
            bubble_sort(niz, vel);
            end = clock();
            break;
        case 2:
            start = clock();
            selection_sort(niz, vel);
            end = clock();
            break;
        case 3:
            start = clock();
            quick_sort(niz, vel);
            end = clock();
            break;
        case 4:
            start = clock();
            merge_sort(niz, vel);
            end = clock();
            break;
        default: goto choice;
    }
    double trajanje = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    if(!check_state(niz, vel)) throw std::logic_error("Niz nije pravilno sortiran. Greska u algoritmu.");
    else std::cout<<"\nNiz sortiran.";
    std::cout<<"\nVrijeme potrebno za sortiranje: "<<std::setprecision(3)<<trajanje<<"ms\n";
    write_to_file("sortirani.txt", niz, vel);
    return 0;
}


int main () {
    while(true) {
        try {
            if(init()==1) break;
        }
        catch(std::exception &e) {
            std::cout<<"\n\nException: "<<e.what()<<"\n";
            return -1;
        }
    }
    return 0;
}