#include <stdexcept>
#include <iostream>
#include <vector>

template <typename T>
class Stek {
private:
    struct Cvor {
        T element;
        Cvor* sljedeci;
        Cvor():element(0), sljedeci(nullptr) {}
        Cvor(const T &el, Cvor *sljedeci=nullptr):element(el), sljedeci(sljedeci) {}
        Cvor(Cvor* sljedeci=nullptr):sljedeci(sljedeci) {}
    };
    Cvor *_vrh;
    int velicina;
public:
    Stek():_vrh(nullptr), velicina(0) {}
    Stek(const Stek &s) {
        Cvor *q, *p(s._vrh);
        _vrh = nullptr;
        velicina = s.velicina;
        while(p!=0) {
            Cvor *n = new Cvor(p->element, nullptr);
            if(_vrh == nullptr) {
                _vrh = n;
                q = _vrh;
            }
            else {
                q->sljedeci = n;
                
                q = n;
            }
            p = p->sljedeci;
        }
    }
    void brisi();
    void stavi(const T &el);
    T skini();
    T& vrh();
    int brojElemenata() { return velicina; }
    bool daLiJePrazan() { return _vrh == 0; }
    Stek &operator=(const Stek &s);
    ~Stek() { brisi(); }

};

template <typename T>
inline void Stek<T>::brisi() {
    while(!daLiJePrazan())
        skini();
}

template<typename T>
inline void Stek<T>::stavi(const T & el) {
    _vrh = new Cvor(el, _vrh);
    ++velicina;
}

template<typename T>
inline T Stek<T>::skini() {
    if(_vrh == nullptr)
        throw std::logic_error("Stek je prazan!");
    T element = _vrh->element;
    Cvor *p = _vrh->sljedeci;
    delete _vrh;
    _vrh = p;
    --velicina;
    return element;
}

template <typename T>
inline T& Stek<T>::vrh() {
    if(this->_vrh==nullptr)
        throw std::logic_error("Stek je prazan!");
    return this->_vrh->element;
}

template <typename T>
inline Stek<T> &Stek<T>::operator=(const Stek &s) {
    if(&s == this)
        return *this;
    this->brisi();
    Cvor *q, *p(s._vrh);
        _vrh = nullptr;
        velicina = s.velicina;
        while(p!=0) {
            Cvor *n = new Cvor(p->element, nullptr);
            if(_vrh == nullptr) {
                _vrh = n;
                q = _vrh;
            }
            else {
                q->sljedeci = n;
                q = n;
            }
            p = p->sljedeci;
        }
        return *this;
}

int binarnaPretraga(const std::vector<int>& vektor, int trazeni) {
    int lijevo = 0, desno = vektor.size() - 1;

    while (lijevo <= desno) {
        int srednji = lijevo + (desno - lijevo) / 2;

        if (vektor[srednji] == trazeni) 
            return srednji;
        else if (vektor[srednji] < trazeni)
            lijevo = srednji + 1;
        else 
            desno = srednji - 1;
    }
    //nije pronađen
    return -1;
}

void pretraga(Stek<std::vector<int> >& s, int trazeni){
    if(s.brojElemenata()==0){
        std::cout<<"Nema elementa";
        return;
    }
    std::vector<int> pomocni(s.vrh());

    if(!pomocni.empty() && pomocni[0]<=trazeni){
        int indeks=binarnaPretraga(pomocni, trazeni);

        if(indeks==-1) std::cout<<"Nema elementa";
        else std::cout<<indeks<<" "<<s.brojElemenata()-1;

        return;
    }
    s.skini();
    pretraga(s, trazeni);
    s.stavi(pomocni);
}

int main() {

    return 0;
}