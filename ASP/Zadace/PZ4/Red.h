#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class Red {
private:
    struct Cvor {
        T element;
        Cvor *sljedeci;
        Cvor(const T &element, Cvor *sljedeci):
            element(element), sljedeci(sljedeci) {}        
    };
    Cvor *pocetak;
    Cvor *kraj;
    int velicina;
    void kopirajRed(const Red &q);
public:
    Red():pocetak(nullptr), kraj(nullptr), velicina(0) {}
    Red(const Red &q) { if(&q!=this) kopirajRed(q); }
    void brisi();
    void stavi(const T &el);
    T skini();
    T& celo() { return pocetak==nullptr ? throw std::logic_error("Red je prazan!") : pocetak->element; }
    int brojElemenata() { return velicina; }
    Red &operator=(const Red &q);
    ~Red() { brisi(); }
};

template<typename T>
inline void Red<T>::kopirajRed(const Red &q) {
    Cvor *p(q.pocetak);
    while(p != nullptr) {
        stavi(p->element);
        p = p->sljedeci;
    }
}

template<typename T>
inline void Red<T>::brisi() {
    while(pocetak!=nullptr)
        skini();
}

template<typename T>
inline void Red<T>::stavi(const T &el) {
    Cvor *n = new Cvor(el, nullptr);
    if(pocetak == nullptr) {
        pocetak = n;
        kraj = n;
        std::cout<<"\nUSAO U IF POCETAK==NULLPTR\n";
    }
    else {
        if(kraj == nullptr)
            std::cout<<"\nKRAJ JE NULLPTR\n";
        kraj->sljedeci = n;
        kraj = kraj->sljedeci;
    }
    ++velicina;
}

template<typename T>
inline T Red<T>::skini() {
    if(pocetak == nullptr)
        throw std::logic_error("Red je prazan!");
    T element = pocetak->element;
    Cvor *p = pocetak;
    if(pocetak == kraj)
        pocetak = kraj = 0;
    else 
        pocetak = pocetak->sljedeci;
    delete p;
    --velicina;
    return element;
}

template<typename T>
inline Red<T> &Red<T>::operator=(const Red &q) {
    if(&q == this)
        return *this;
    brisi();
    kopirajRed(q);
    return *this;
}