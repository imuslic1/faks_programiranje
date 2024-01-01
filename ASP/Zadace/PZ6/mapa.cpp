#include <iostream>
#include <stdexcept>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
/**
 * @brief Abstract class for NizMapa to be derived from  
 * 
 * @tparam K data type for the Key of an entry
 * @tparam V data type for the Value of an entry
 */
template <typename K, typename V>
class Mapa {
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual V operator[](K key) const = 0;
    virtual V &operator[](K key) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const K& key) = 0;
};

/**
 * @brief Map implemented as a dynamically allocated array of std::pair<K, V>
 * 
 * @tparam K template data type for Key
 * @tparam V template data type for Value. Must be a comparable data type (with comparing operators defined)
 */

template <typename K, typename V> 
class NizMapa : public Mapa<K,V> {
    std::pair<K, V> *mapa;
    int _velicina, _kapacitet;
    /**
     * @brief Fully reallocates the array when it is full. Changes capacity to 2x the previous.
     * 
     */
    void _realloc() {
        _kapacitet *= 2;
        std::pair<K, V>* novaMapa = new std::pair<K,V>[_kapacitet]();
        for(int i=0; i<_velicina; ++i)
            novaMapa[i] = mapa[i];
        
        delete[] mapa;
        mapa = novaMapa;
    }
public:
    NizMapa(int pocetniKapacitet = 10) : _kapacitet(pocetniKapacitet), _velicina(0) {
        mapa = new std::pair<K, V>[_kapacitet]();
    }

    NizMapa(const NizMapa &druga) : _velicina(druga._velicina), _kapacitet(druga._kapacitet) {
        mapa = new std::pair<K, V>[_kapacitet]();
        for(int i=0; i<_velicina; ++i)
            mapa[i] = druga.mapa[i];
    }

    NizMapa &operator=(const NizMapa &druga) {
        if(this!= &druga) {
            delete[] mapa;
            _velicina = druga._velicina;
            _kapacitet = druga._kapacitet;
            mapa = new std::pair<K, V>[_kapacitet]();
            for(int i=0; i<_velicina; ++i)
                mapa[i] = druga.mapa[i];
        }
        return *this;
    }

    ~NizMapa() { delete[] mapa; }
    V operator[](K key) const override {
        for(int i=0; i<_velicina; ++i)
            if(mapa[i].first == key)
                return mapa[i].second;
        
        return V();    
    }
    V &operator[](K key) override {
        for(int i=0; i<_velicina; ++i)
            if(mapa[i].first == key)
                return mapa[i].second;
        
        if(_velicina == _kapacitet)
            _realloc();
        
        mapa[_velicina++] = std::make_pair(key, V());
        return mapa[_velicina-1].second;
    }
    
    int brojElemenata() const override { return _velicina; }
    /**
     * @brief Sets _velicina to 0, effectively deleting all of the entries from the map. 
     * New entries will overwrite the existing ones, eliminating the need to reallocate.
     * 
     */
    void obrisi() override { _velicina = 0; }
    /**
     * @brief Deletes the entry with the key provided by the parameter, while also 
     * freeing the memory taken by it.
     * 
     * @param key Key to be deleted.
     */
    void obrisi(const K &key) override {
        for(int i=0; i<_velicina; ++i) {
            if(mapa[i].first == key) {
                for(int j=i; j<_velicina - 1; ++j)
                    mapa[j] = mapa[j+1];
                --_velicina;
                return;
            }
        }
        throw std::logic_error("Mapa ne sadrži zapis sa datim ključem!");
    }

    void print() const {
        for(int i=0; i<_velicina; ++i)
            std::cout<<"Key: "<<mapa[i].first<<", Value: "<<mapa[i].second<<std::endl;
    }
};

void Test1() {
    std::cout<<"\n***TEST 1: NizMapa<int, std::string>***\n";
    NizMapa<int, std::string> kantoni;
    kantoni[1] = "USK";
    kantoni[2] = "PK";
    kantoni[3] = "TK";
    kantoni[4] = "ZDK";
    kantoni[5] = "BPK";
    kantoni[6] = "SBK";
    kantoni[7] = "HNK";
    kantoni[8] = "ZHK";
    kantoni[9] = "KS";
    kantoni[10] = "K10";
    std::cout<<"Kantoni: \n";
    kantoni.print();
    kantoni.obrisi(8);
    std::cout<<"\nObrisan key 8.\n";
    kantoni.print();
}

void Test2() {
    std::cout<<"\n***TEST 2: NizMapa<std::string, short>***\n";
    NizMapa<std::string, short> studenti;
    studenti["Ismar Muslić"] = 19304;
    studenti["Mujo Mujić"] = 13579;
    studenti["Fata Fatić"] = 13468;

    std::cout<<"\nUkupno je: "<<studenti.brojElemenata()<<" studenata.\n";
    studenti.print();
}

void Test3() {
    std::cout<<"\n***TEST 3: NizMapa<std::string, double>***\n";
    std::cout<<"\nNeke poznate matematicke konstante: \n";
    NizMapa<std::string, double> konstante;
    konstante["Pi"] = 4*atan(1);
    konstante["e"] = 2.718281828459045235360287471352;
    konstante["Pitagorina konstanta"] = sqrt(2);
    konstante["Zlatni rez"] = 2*sin(0.942478);
    konstante["Treći prirodni broj"] = 3;

    auto kopija = konstante;
    kopija.print();
    konstante.obrisi();
    std:cout<<"Konstante uspjesno obrisane.\n";
    kopija.obrisi();
}

void Test4() {
    std::cout<<"\n***TEST 4: NizMapa<float, char>***\n";
    NizMapa<float, char> mapa;
    mapa[1.1f] = 'A';
    mapa[2.2f] = 'B';
    mapa[3.3f] = 'C';
    std::cout << "Broj elemenata: " << mapa.brojElemenata() << std::endl;
    mapa.print();
}

void Test5() {
    std::cout<<"\n***TEST 5: NizMapa<char, char>***\n";
    NizMapa<char, char> mapa;
    mapa['A'] = 'a';
    mapa['B'] = 'b';
    mapa['C'] = 'c';
    mapa['D'] = 'd';
    std::cout << "Broj elemenata: " << mapa.brojElemenata() << std::endl;
    mapa.print();
    mapa.obrisi();
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}