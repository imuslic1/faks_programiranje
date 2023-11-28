#include <iostream>
#include <stdexcept>

using std::cout;
/**
 * @brief Apstraktna klasa Lista, iz koje su izvedene JednostrukaLista,
 * DvostrukaLista i NizLista
 * 
 * @tparam T - bilo koji POD tip podatka koji ce vaziti za elemente liste
 */
template <typename T> class DvostrukaIterator;

template <typename T> class Lista {
public:
    Lista() {}
    virtual ~Lista() {}
    virtual int brojElemenata() const = 0;
    virtual T &trenutni() = 0;
    virtual T trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const T &el) = 0;
    virtual void dodajIza(const T &el) = 0;
    virtual T &operator[](int i) = 0;
    virtual T operator[](int i) const = 0;
};

template <typename T> class DvostrukaLista : public Lista<T> {
private:
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
                if(sljedeci != 0)
                    sljedeci->prethodni = this;
            }
    };
    
    Cvor *_prvi, *_posljednji, *_trenutni;
    int velicina, duzina_D, duzina_L;
    void Initialize();
    void Destroy();

    friend class DvostrukaIterator<T>;
public:
    DvostrukaLista(){ Initialize(); }
    ~DvostrukaLista() { Destroy(); }
    DvostrukaLista(const DvostrukaLista<T> &dl);
    DvostrukaLista<T> &operator=(const DvostrukaLista<T> &dl);
    int brojElemenata() const override { return velicina; }
    T trenutni() const override;
    T &trenutni() override;
    bool prethodni() override;
    bool sljedeci() override;
    void pocetak() override;
    void kraj() override;
    void obrisi() override;
    void dodajIspred(const T &el) override;
    void dodajIza(const T &el) override;
    T operator[](int i) const override;
    T &operator[](int i) override;    
};

template <typename T>
void DvostrukaLista<T>::Destroy() {
    while (_prvi != nullptr) {
        Cvor *temp = _prvi;
        _prvi = _prvi->sljedeci;
        delete temp;
        }
    _posljednji=nullptr; _trenutni = nullptr;
}

template <typename T>
void DvostrukaLista<T>::Initialize() {
    _prvi = _posljednji = _trenutni = new Cvor(nullptr, nullptr);
    velicina = duzina_D = duzina_L = 0;
}

template <typename T>
DvostrukaLista<T>::DvostrukaLista(const DvostrukaLista<T> &dl) {
    velicina = dl.velicina;
    if(velicina == 0) {
        _prvi = _posljednji = _trenutni = nullptr;
        duzina_D = duzina_L = 0;
        return;
    }
    
    _prvi = new Cvor();
    Cvor *temp1 = dl._prvi->sljedeci;
    Cvor *temp2 = _prvi;

    while(temp1 != nullptr) {
        temp2->sljedeci = new Cvor(temp1->element);
        temp2->sljedeci->prethodni = temp2;
        temp1 = temp1->sljedeci;
        temp2 = temp2->sljedeci;
    }

    _posljednji = temp2;
    _trenutni = _prvi;
    duzina_L = 1;
    duzina_D = velicina - 1;
}

template <typename TipEl>
DvostrukaLista<TipEl> &
DvostrukaLista<TipEl>::operator=(const DvostrukaLista<TipEl> &dl) {
    if(&dl == this)
        return *this;
    this->Destroy();

    velicina = dl.velicina;
    if(velicina == 0) {
        _prvi = _posljednji = _trenutni = nullptr;
        duzina_D = duzina_L = 0;
        return *this;
    }
    _prvi = new Cvor();
    Cvor *temp1 = dl._prvi->sljedeci;
    Cvor *temp2 = _prvi;

    while(temp1 != nullptr) {
        temp2->sljedeci = new Cvor(temp1->element);
        temp2->sljedeci->prethodni = temp2;
        temp1 = temp1->sljedeci;
        temp2 = temp2->sljedeci;
    }

    _posljednji = temp2;
    _trenutni = _prvi;
    duzina_L = 1;
    duzina_D = velicina - 1;

    return *this;
}

template <typename T> T &DvostrukaLista<T>::trenutni() {
  if(velicina == 0)
    throw std::range_error("Lista je prazna");
  return (_trenutni->sljedeci)->element;
}

template <typename T> T DvostrukaLista<T>::trenutni() const {
  if(velicina == 0)
    throw std::range_error("Lista je prazna");
  return (_trenutni->sljedeci)->element;
}

template <typename T> bool DvostrukaLista<T>::prethodni() {
    if(velicina == 0)
        throw std::range_error("Lista je prazna");
    if(duzina_L == 1)
        return false;
    
    _trenutni = _trenutni->prethodni;
    --duzina_L;
    ++duzina_D;
    return true;
}

template <typename T> bool DvostrukaLista<T>::sljedeci() {
    if(velicina == 0)
        throw std::logic_error("Lista je prazna");
    if(duzina_D == 0)
        return false;
    _trenutni = _trenutni->sljedeci;
    ++duzina_L;
    --duzina_D;
    return true;
}

template <typename T> void DvostrukaLista<T>::pocetak() {
  if (velicina == 0)
    throw std::range_error("Lista je prazna");
  _trenutni = _prvi;
  duzina_L = 1;
  duzina_D = velicina - 1;
}

template <typename T> void DvostrukaLista<T>::kraj() {
    if (velicina == 0)
        throw std::range_error("Lista je prazna");
    _trenutni = _posljednji->prethodni;
}

template <typename T> void DvostrukaLista<T>::obrisi() {
    if(velicina == 0 || _trenutni == nullptr)
        throw std::range_error("Lista je prazna");
    if(duzina_D == 0) {
        delete _posljednji;
        _trenutni->sljedeci = nullptr;
        _posljednji = _trenutni;
        prethodni();
        --duzina_D;
        --velicina;
        return;
    }

    Cvor *temp = (_trenutni->sljedeci)->sljedeci;
    delete _trenutni->sljedeci;
    _trenutni->sljedeci = temp;
    --duzina_L;
    --velicina;
}

template <typename T> void DvostrukaLista<T>::dodajIspred(const T &el) {
    Cvor *newCvor = new Cvor(el, _trenutni->sljedeci, _trenutni);
    if(velicina == 0) {
        _prvi->sljedeci = newCvor;
        _posljednji = newCvor;
    } else {
        _trenutni->sljedeci = newCvor;
        _trenutni = newCvor;
    }
    ++velicina;
    ++duzina_L;
}

template <typename T> void DvostrukaLista<T>::dodajIza(const T &el) {
    if(velicina == 0) {
        Cvor *newCvor = new Cvor(el, _prvi->sljedeci, _prvi);
        _prvi->sljedeci = newCvor;
        _posljednji = newCvor;
        ++velicina;
        ++duzina_L;
        return;
    }
    Cvor *newCvor = new Cvor(el, (_trenutni->sljedeci)->sljedeci, _trenutni->sljedeci);
    (_trenutni->sljedeci)->sljedeci = newCvor;

    if(_trenutni->sljedeci == _posljednji)
        _posljednji = newCvor;
    ++velicina;
    ++duzina_D;
}

template <typename T> T &DvostrukaLista<T>::operator[](int i) {
    if(i<0 || i>=velicina)
        throw std::range_error("Indeks nije validan");

    Cvor *temp = _prvi->sljedeci;
    for (int j=0; j<i; ++j)
        temp = temp->sljedeci;

    return temp->element;
}

template <typename T> T DvostrukaLista<T>::operator[](int i) const {
    if(i<0 || i>=velicina) {
        throw std::range_error("Indeks nije validan");
    }

    Cvor *temp = _prvi->sljedeci;
        for (int j=0; j<i; ++j)
            temp = temp->sljedeci;

    return temp->element;
}

template <typename T> class DvostrukaIterator {
private:
    const DvostrukaLista<T> &lista;
    typename DvostrukaLista<T>::Cvor *kursor;
public:
    DvostrukaIterator(const DvostrukaLista<T> &lista)
        : lista(lista), kursor(lista._trenutni) {}

    void operator++() { kursor = kursor->sljedeci; }
    void operator--() { kursor = kursor->prethodni; }
    void operator++(int) { kursor = kursor->sljedeci; }
    void operator--(int) { kursor = kursor->prethodni; }
    T &operator*() const { return kursor->element; }
    T operator->() const { return &(kursor->element); }
    bool operator==(const DvostrukaIterator &drugi) const {
        return kursor == drugi.kursor;
    }
    bool operator!=(const DvostrukaIterator &drugi) const {
        return kursor != drugi.kursor;
    }
    DvostrukaIterator<T> begin() {
        DvostrukaIterator<T> temp(lista);
        temp.kursor = lista._prvi->sljedeci;
        return temp;
    }

    DvostrukaIterator<T> end() {
        DvostrukaIterator<T> temp(lista);
        temp.kursor = lista._posljednji;
        return temp;
    }
    void setBegin() { kursor = lista._prvi; }
};

template <typename T>
T dajMaksimum (const Lista<T> &n) {
    if(n.brojElemenata()==0)
        throw std::logic_error("Lista je prazna");
    DvostrukaIterator<T> it(dynamic_cast<const DvostrukaLista<T> &>(n));
    it.setBegin();

    T najveci = *it;
    while(it != it.end()) {
        if(*it>najveci)
            najveci = *it;
        ++it;
    }
    return najveci;
}


template <typename T> void brElemenata_test(Lista<T> &l) {
    std::cout<<"\nBroj elemenata je: "<<l.brojElemenata()<<"\n";
}

template <typename T> void trenutni_test(Lista<T> &l) {
    try {
        std::cout<<"Trenutni element je: "<<l.trenutni()<<"\n";
        std::cout<<"\nUmanjen za 1: "<<--l.trenutni()<<"\n";
    } catch (std::exception &e) {
        std::cout<<"\n***IZUZETAK: "<<e.what()<<"\n";
    }
}


template <typename T> void prethodni_test(Lista<T> &l) {
    if(l.prethodni()) std::cout<<"prethodni() uspjesno izvrsen!\n";
    else std::cout<<"prethodni neuspjesan.\n";
}

template <typename T> void sljedeci_test(Lista<T> &l) {
    if(l.prethodni()) std::cout<<"sljedeci() uspjesno izvrsen!\n";
    else std::cout<<"sljedeci() neuspjesan.\n";
}


template <typename T> void pocetak_test(Lista<T> &l) {
    try {
        l.pocetak();
        std::cout<<"pocetak() uspjesno izvrsen!\n";
    } catch (std::exception &e) {
        std::cout<<"\n***Failed to execute pocetak(): "<<e.what()<<"\n";
    }
}

template <typename T> void kraj_test(Lista<T> &l) {
    try {
        l.kraj();
        std::cout<<"kraj() uspjesno izvrsen!\n";
    } catch (std::exception &e) {
        std::cout<<"\n***Failed to execute kraj(): "<<e.what()<<"\n";
    }
}

template <typename T> 
void dodajIspred_test(Lista<T> &l, const T el) {
    l.dodajIspred(el); 
    std::cout << el << " uspjesno dodanIspred()!\n";
}

template <typename T> 
void dodajIza_test(Lista<T> &l, const T el) {
    l.dodajIza(el); 
    std::cout << el << " uspjesno dodanIza()!\n";
}

template <typename T> void obrisi_test(Lista<T> &l) {
    l.obrisi();
    std::cout<<"obrisi() uspjesno izvrsen.\n";
}

/******************************
 *
 * main(): testovi
 *
 *******************************/

int main() {
    DvostrukaLista<int> lista;
    lista.dodajIza(1);
    lista.dodajIza(2);
    lista.dodajIza(3);
    lista.dodajIza(4);
    lista.dodajIza(5);
    for(int i=5; i<=100; ++i)
        lista.dodajIspred(i);

    std::cout<<"\nMOJ TEST: \n";
    brElemenata_test(lista);
    trenutni_test(lista);
    prethodni_test(lista);
    sljedeci_test(lista);
    kraj_test(lista);
    dodajIspred_test(lista, 77);
    dodajIza_test(lista, 22);
    obrisi_test(lista);

    std::cout<<"\nMaksimum: "<<dajMaksimum(lista);
}