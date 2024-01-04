#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <chrono>

using sat = std::chrono::high_resolution_clock;

using std::cin;
using std::cout;
using std::endl;

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

template <typename K, typename V>
class BinStabloMapa : public Mapa<K, V>
{
    struct Cvor {
        K kljuc;
        V vrijednost;
        Cvor *l_dijete, *d_dijete, *roditelj;

        Cvor(K i = K(), V u = V()) : kljuc(i), vrijednost(u), 
            d_dijete(nullptr), l_dijete(nullptr),
            roditelj(nullptr) {}
    };

    Cvor *novi(K i = K(), V u = V()) {
        Cvor *temp = new Cvor();
        temp->kljuc = i;
        temp->vrijednost = u;
        temp->d_dijete = temp->l_dijete = temp->roditelj = nullptr;
        return temp;
    }

    Cvor *pretraga(Cvor *p, K i) const {
        if(p==nullptr || p->kljuc==i)
            return p;
        if(p->kljuc < i)
            return pretraga(p->d_dijete, i);
        else if(p->kljuc > i)
            return pretraga(p->l_dijete, i);
        return p;
    }

    Cvor *dodaj(Cvor *p, K i, V u = V(), Cvor *rod = nullptr) {
        if(p==nullptr) {
            p = novi(i, u);
            p->roditelj = rod;
            return p;
        }
        if(i > p->kljuc)
            p->d_dijete = dodaj(p->d_dijete, i, u, p);
        else
            p->l_dijete = dodaj(p->l_dijete, i, u, p);
        return p;
    }

    Cvor *nasljednik(Cvor *t) {
        auto trenutni = t;
        while(trenutni && trenutni->l_dijete != nullptr)
            trenutni = trenutni->l_dijete;
        return trenutni;
    }

    void konstruktor(Cvor *a, Cvor *b) {
        if(b == nullptr)
            return;
        konstruktor(a, b->l_dijete);
        konstruktor(a, b->d_dijete);
        dodaj(a, b->kljuc, b->vrijednost);
    }

    Cvor *obrisiC(Cvor *t, K i) {
        if(t == nullptr)
            return t;
        if(i < t->kljuc)
            t->l_dijete = obrisiC(t->l_dijete, i);
        else if(i > t->kljuc)
            t->d_dijete = obrisiC(t->d_dijete, i);
        else {
            if(t->l_dijete == nullptr) {
                Cvor *temp = t->d_dijete;
                delete t;
                return temp;
            }
            else if(t->d_dijete == nullptr) {
                Cvor *temp = t->l_dijete;
                delete t;
                return temp;
            }

            auto q = nasljednik(t->d_dijete);
            t->kljuc = q->kljuc;
            t->vrijednost = q->vrijednost;
            t->d_dijete = obrisiC(t->d_dijete, q->kljuc);
        }
        return t;
    }

    void obrisi_stablo(Cvor *t) {
        if(t==nullptr)
            return;
        obrisi_stablo(t->l_dijete);
        obrisi_stablo(t->d_dijete);
        delete t;
    }
    int _velicina;
    Cvor *p;

public:
    BinStabloMapa<K, V>() : _velicina(0), p(nullptr) {}
    ~BinStabloMapa<K, V>() { obrisi_stablo(p); }
    BinStabloMapa<K, V>(const BinStabloMapa<K, V> &a) {
        _velicina = a._velicina;
        if(a._velicina==0)
            p = nullptr;
        else {
            p = novi(a.p->kljuc, a.p->vrijednost);
            konstruktor(p, a.p);
        }
    }

    BinStabloMapa<K, V> &operator=(const BinStabloMapa<K, V> &a) {
        if(this == &a)
            return *this;

        obrisi();
        _velicina = a._velicina;
        if(a._velicina == 0)
            p = nullptr;
        else {
            p->kljuc = a.p->kljuc;
            p->vrijednost = a.p->vrijednost;
            konstruktor(p, a.p);
        }
        return *this;
    }

    int brojElemenata() const override { return _velicina; }

    void obrisi() override {
        obrisi_stablo(p);
        p = novi();
        _velicina = 0;
    }

    void obrisi(const K &kljuc) override {
        if(p->kljuc == kljuc)
            p = obrisiC(p, kljuc);
        else
            obrisiC(p, kljuc);
        --_velicina;
    }

    V &operator[](K i) override {
        if(p==nullptr) {
            p = novi(i);
            ++_velicina;
            return p->vrijednost;
        }
        auto c = pretraga(p, i);
        if(c == nullptr) {
            dodaj(p, i);
            ++_velicina;
            c = pretraga(p, i);
        }
        return c->vrijednost;
    }

    V operator[](K i) const override {
        auto c = pretraga(p, i);
        if(c != nullptr)
            return c->vrijednost;
        return V();
    }
};

/**
 * Testirano na mašini sa Intel Core i5-8300h quad-core procesorom, 
 * sa 5 testnih pokretanja programa, na 30000 elemenata, 
 * prosječan rezultat je sljedeći:
 * 
 *      PROSJEK NizMapa ubacivanje: 979027 mi s
 *      PROSJEK BinStablo ubacivanje: 11260 mi s
 *      PROSJEK NizMapa pristup: 89 mi s 
 *      PROSJEK BinStablo pristup: 1.2 mi s
 * 
 * Iz ovih podataka se zaključuje da je BinStablo mapa u prosjeku 
 * 86.94x brža pri umetanju elemenata nego NizMapa. 
 * 
 * Prilikom pristupa elementima se također primijeti ubrzanje od oko
 * 90x. Dodatni stepen indirekcije koji se mogao koristiti 
*/

int main()
{
    BinStabloMapa<int, double> t;
    NizMapa<int, double> m;

    auto start = sat::now();
    for (int i = 0; i < 30000; i++)
        m[std::rand()] = 1. / std::rand();
    auto end = sat::now();

    auto w = std::setw(40);
    auto l = std::left;

    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<w<<l<<"Vrijeme umetanja (NizMapa): "<<time.count()<< " mikrosekundi\n";

    start = sat::now();
    m[std::rand()] = std::rand();
    end = sat::now();

    time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<w<<l<<"Vrijeme pristupa (NizMapa): "<<l<<time.count()<<" mikrosekundi\n";

    start = sat::now();
    for (int i = 0; i < 20000; i++)
        t[std::rand()] = 1. / std::rand();
    end = sat::now();

    time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<w<<l<<"Vrijeme umetanja (BinStabloMapa): "<<time.count()<< " mikrosekundi\n";

    start = sat::now();
    t[std::rand()] = std::rand();
    end = sat::now();

    time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<<w<<l<<"Vrijeme pristupa (BinStabloMapa): "<<time.count()<<" mikrosekundi\n";

    return 0;
}