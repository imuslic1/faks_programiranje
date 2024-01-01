#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

template <typename T> class DvostraniRed {
    struct Cvor {
        T element;
        Cvor *sljedeci, *prethodni;
        Cvor(const T &el, Cvor *sljedeci=nullptr, Cvor *prethodni=nullptr)
            : element(el), sljedeci(sljedeci), prethodni(prethodni) {
                if(prethodni != nullptr)
                    prethodni->sljedeci = this;
                if(sljedeci != nullptr)
                    sljedeci->prethodni = this;
            }

        Cvor(Cvor *sljedeci = nullptr, Cvor *prethodni=nullptr) 
            : sljedeci(sljedeci), prethodni(prethodni) {
                if(prethodni != nullptr)
                    prethodni->sljedeci = this;
                if(sljedeci != nullptr)
                    sljedeci->prethodni = this;
            }
    };
    //zadnji element u redu
    Cvor *_vrh;
    //prvi element u redu
    Cvor *_celo;
    int velicina;
    /**
     * @brief kopira u red nad kojim je pozvana sve elemente parametra
     * 
     * @param q red to be copied 
     */
    void kopirajRed(const DvostraniRed &q);
public:
    DvostraniRed():vrh(nullptr), celo(nullptr), velicina(0) {}
    DvostraniRed(DvostraniRed &deq) { if(&deq!=this) kopirajRed(deq); }
    /**
     * @brief Brise sve elemente iz reda
     */
    void brisi();
    /**
     * @brief Stavlja novi element na vrh reda. 
     * Vrh reda je posljednji element koji dolazi na red
     * 
     * @param el vrijednost elementa koja ce biti postavljena u novi Cvor
     */
    void staviNaVrh(const T &el);
    T skiniSaVrha();
    /**
     * @brief Stavlja novi element na celo reda.
     * Celo reda je prvi element koji dolazi na red.
     * 
     * @param el vrijednost elementa koja ce biti postavljena
     */
    void staviNaCelo(const T &el);
    T skiniSaCela();
    //vraca zadnji element u redu
    T& vrh() { return _vrh->element; };
    //vraca prvi element u redu
    T& celo() { return _celo->element; };
    DvostraniRed &operator=(const DvostraniRed &deq);
    ~DvostraniRed() { brisi(); }
};

template<typename T>
inline void DvostraniRed<T>::kopirajRed(const DvostraniRed &deq) {
    Cvor *p(deq.vrh);
    while(p != nullptr) {
        staviNaVrh(p->element);
        p = p->sljedeci;
    }
}

template <typename T>
inline void DvostraniRed<T>::brisi() {
    while(velicina!=0)
        skiniSaCela();
}

template<typename T>
inline void DvostraniRed<T>::staviNaVrh(const T &el) {
    Cvor *temp = new Cvor(el);
    if(_vrh==nullptr)
        _celo = _vrh = temp;
    else {
        temp->prethodni = _vrh;
        _vrh->sljedeci = temp;
        _vrh = temp;
    }
    ++velicina;
}

template <typename T>
inline void DvostraniRed<T>::staviNaCelo(const T& el) {
    Cvor *temp = new Cvor(el);
    if(_celo==nullptr)
        _celo = _vrh = temp;
    else {
        temp->sljedeci = _celo;
        _celo->prethodni = temp;
        _celo = temp;
    }
    ++velicina;
}

template <typename T>
inline T DvostraniRed<T>::skiniSaVrha() {
    Cvor *temp = new Cvor(_vrh);
    if(_vrh == nullptr)
        throw std::logic_error("Red je prazan!");
    T vrijednost = temp->element;
    _vrh = _vrh->prethodni;
    delete temp;
    --velicina;
    return vrijednost;
}

template <typename T>
inline T DvostraniRed<T>::skiniSaCela() {
    Cvor *temp = new Cvor(_celo);
    if(_celo == nullptr)
        throw std::logic_error("Red je prazan!");
    T vrijednost = temp->element;
    _celo = _celo->sljedeci;
    delete temp;
    --velicina;
    return vrijednost;
}

template <typename T>
inline DvostraniRed<T> &DvostraniRed<T>::operator=(const DvostraniRed& deq) {
    if(&q == this)
        return *this;
    brisi();
    kopirajRed(deq);
    return *this;
}