#include <bits/stdc++.h>
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

template <typename T> 
class NizLista : public Lista<T> {
  T **lista;
  int velicina, kapacitet;
  int _trenutni, _kraj;
  void realloc();

public:
  NizLista(int novi_kapacitet = 100)
      : velicina(0), kapacitet(novi_kapacitet), _trenutni(0), _kraj(0) {
    lista = new T *[novi_kapacitet]();
  }

  ~NizLista() {
    for (int i = 0; i < velicina; i++)
      delete lista[i];
    delete[] lista;
  }

  NizLista(const NizLista<T> &l);
  NizLista<T> &operator=(const NizLista<T> &l);
  int brojElemenata() const override { return velicina; }
  T &trenutni() override;
  T trenutni() const override;
  bool prethodni() override;
  bool sljedeci() override;
  void pocetak() override;
  void kraj() override;
  void obrisi() override;
  void dodajIspred(const T &el) override;
  void dodajIza(const T &el) override;
  T &operator[](int i) override;
  T operator[](int i) const override;
};

template <typename T> class JednostrukaLista : public Lista<T> {
private:
  struct Cvor {
    T element;
    Cvor *sljedeci;
    Cvor(const T &el, Cvor *sljedeci = nullptr)
        : element(el), sljedeci(sljedeci) {}
    Cvor(Cvor *sljedeci = nullptr) : sljedeci(sljedeci) {}
  };
  Cvor *_prvi, *_posljednji, *_trenutni;
  int velicina, duzina_D, duzina_L;

public:
  JednostrukaLista()
      : _prvi(new Cvor(nullptr)), _posljednji(_prvi), _trenutni(_prvi),
        velicina(0), duzina_D(0), duzina_L(0) {}
  ~JednostrukaLista() {
    while (_prvi != nullptr) {
      Cvor *temp = _prvi;
      _prvi = _prvi->sljedeci;
      delete temp;
    }
  }
  JednostrukaLista(const JednostrukaLista<T> &jl);
  JednostrukaLista<T> &operator=(const JednostrukaLista<T> &jl);
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

/******************************
 *
 * Implementacija NizListe:
 *
 *******************************/

template <typename T> void NizLista<T>::realloc() {
  int novi_kapacitet = 2 * kapacitet;
  T **novaLista = new T *[novi_kapacitet]();
  for (int i = 0; i < velicina; i++)
    novaLista[i] = lista[i];
  delete[] lista;
  lista = novaLista;
  kapacitet = novi_kapacitet;
}

template <typename T> NizLista<T>::NizLista(const NizLista<T> &l) {
  velicina = l.brojElemenata();
  kapacitet = l.kapacitet;
  lista = new T *[kapacitet];
  for (int i = 0; i < l.brojElemenata(); i++)
    lista[i] = new T(*l.lista[i]);
}

template <typename T>
NizLista<T> &NizLista<T>::operator=(const NizLista<T> &l) {
  if (this == &l)
    return *this;
  while (this->kapacitet < l.kapacitet)
    this->realloc();
  for (int i = 0; i < velicina; i++)
    delete this->lista[i];
  velicina = l.velicina;
  for (int i = 0; i < l.brojElemenata(); i++)
    lista[i] = new T(*l.lista[i]);
  return *this;
}

template <typename T> T &NizLista<T>::trenutni() {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  return *(lista[_trenutni]);
}
template <typename T> T NizLista<T>::trenutni() const {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  return *(lista[_trenutni]);
}
template <typename T> bool NizLista<T>::prethodni() {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  if (_trenutni > 0) {
    --_trenutni;
    return true;
  }
  return false;
}

template <typename T> bool NizLista<T>::sljedeci() {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  if (_trenutni != _kraj) {
    ++_trenutni;
    return true;
  }
  return false;
}
template <typename T> void NizLista<T>::pocetak() {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  _trenutni = 0;
}

template <typename T> void NizLista<T>::kraj() {
  if (this->velicina == 0)
    throw std::logic_error("Lista je prazna!");
  _trenutni = _kraj;
}

template <typename T> void NizLista<T>::obrisi() {
  if (this->velicina <= 0)
    throw std::logic_error("Lista je prazna!");
  delete lista[_trenutni];
  for (int i = _trenutni; i < velicina - 1; i++)
    lista[i] = lista[i + 1];
  lista[velicina - 1] = nullptr;
  if (_trenutni == velicina - 1 && _trenutni != 0)
    --_trenutni;
  --velicina;
}

template <typename T> void NizLista<T>::dodajIspred(const T &el) {
  if (velicina >= kapacitet) // kada ima potreba za realokacijom
    this->realloc();
  if (velicina == 0) { // prvi element
    lista[0] = new T(el);
    //_trenutni = 0;
    //++_kraj;
    ++velicina;
    return;
  }
  // dodavanje ako nije specijalni slucaj:
  ++_kraj;
  for (int i = _kraj; i > _trenutni; --i)
    lista[i] = lista[i - 1];
  lista[_trenutni] = new T(el);
  ++_trenutni;
  ++velicina;
}

template <typename T> void NizLista<T>::dodajIza(const T &el) {
  if (velicina >= kapacitet) // kada ima porebe za realokacijom
    this->realloc();
  if (velicina == 0) { // prvi element
    lista[0] = new T(el);
    //_trenutni = 0;
    //++_kraj;
    ++velicina;
    return;
  }
  // dodavanje ako nije specijalan slucaj:
  ++_kraj;
  for (int i = _kraj; i > _trenutni + 1; --i)
    lista[i] = lista[i - 1];
  lista[_trenutni + 1] = new T(el);
  ++velicina;
}
template <typename T> T &NizLista<T>::operator[](int i) {
  if (i >= 0 && i <= velicina) {
    return *(lista[i]);
  }
  throw std::range_error("Indeks nije validan");
}

template <typename T> T NizLista<T>::operator[](int i) const {
  if (i >= 0 && i <= velicina) {
    return *(lista[i]);
  }
  throw std::range_error("Indeks nije validan");
}

/******************************
 *
 * Implementacija JednostrukeListe:
 *
 *******************************/

template <typename T>
JednostrukaLista<T>::JednostrukaLista(const JednostrukaLista<T> &jl) {
  velicina = jl.velicina;
  _prvi = new Cvor();
  Cvor *temp1 = jl._prvi->sljedeci;
  Cvor *temp2 = _prvi;

  while (temp1 != nullptr) {
    temp2->sljedeci = new Cvor(temp1->element);
    temp1 = temp1->sljedeci;
    temp2 = temp2->sljedeci;
  }

  _posljednji = temp2;
  _trenutni = _prvi;
  if (velicina > 0) {
    duzina_L = 1;
    duzina_D = velicina - 1;
  }
}

template <typename TipEl>
JednostrukaLista<TipEl> &
JednostrukaLista<TipEl>::operator=(const JednostrukaLista<TipEl> &jl) {
  while (_prvi != nullptr) {
    Cvor *temp = _prvi;
    _prvi = _prvi->sljedeci;
    delete temp;
  }
  velicina = jl.velicina;
  _prvi = new Cvor();
  Cvor *temp1 = jl._prvi->sljedeci;
  Cvor *temp2 = _prvi;

  while (temp1 != nullptr) {
    temp2->sljedeci = new Cvor(temp1->element);
    temp1 = temp1->sljedeci;
    temp2 = temp2->sljedeci;
  }
  _posljednji = temp2;
  _trenutni = _prvi;
  if (velicina > 0) {
    duzina_L = 1;
    duzina_D = velicina - 1;
  }
  return *this;
}

template <typename T> T &JednostrukaLista<T>::trenutni() {
  if (velicina == 0)
    throw std::range_error("Lista je prazna");
  return (_trenutni->sljedeci)->element;
}

template <typename T> T JednostrukaLista<T>::trenutni() const {
  if (velicina == 0)
    throw std::range_error("Lista je prazna");
  return (_trenutni->sljedeci)->element;
}

template <typename T> bool JednostrukaLista<T>::prethodni() {
  if (velicina == 0)
    throw std::range_error("Lista je prazna");
  if (duzina_L == 1)
    return false;
  Cvor *prethodni = _prvi;
  while (prethodni->sljedeci != _trenutni)
    prethodni = prethodni->sljedeci;

  _trenutni = prethodni;
  --duzina_L;
  ++duzina_D;
  return true;
}

template <typename T> bool JednostrukaLista<T>::sljedeci() {
  if (velicina == 0)
    throw std::logic_error("Lista je prazna");
  if (duzina_D == 0)
    return false;
  _trenutni = _trenutni->sljedeci;
  duzina_L++;
  duzina_D--;
  return true;
}

template <typename T> void JednostrukaLista<T>::pocetak() {
  if (velicina == 0)
    throw std::range_error("Prazna lista");
  _trenutni = _prvi;
  duzina_L = 1;
  duzina_D = velicina - 1;
}

template <typename T> void JednostrukaLista<T>::kraj() {
  if (velicina == 0)
    throw std::range_error("Prazna lista");
  _trenutni = _prvi->sljedeci;

  while (_trenutni->sljedeci != _posljednji)
    _trenutni = _trenutni->sljedeci;
}

template <typename T> void JednostrukaLista<T>::obrisi() {
  if (velicina == 0 || _trenutni == nullptr)
    throw std::range_error("Prazna lista");
  if (duzina_D == 0) {
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

template <typename T> void JednostrukaLista<T>::dodajIspred(const T &el) {
  Cvor *newCvor = new Cvor(el, _trenutni->sljedeci);
  if (velicina == 0) {
    _prvi->sljedeci = newCvor;
    _posljednji = newCvor;
    ++velicina;
    ++duzina_L;
    return;
  }
  _trenutni->sljedeci = newCvor;
  _trenutni = newCvor;
  ++velicina;
  ++duzina_L;
}

template <typename T> void JednostrukaLista<T>::dodajIza(const T &el) {
  if (velicina == 0) {
    Cvor *newCvor = new Cvor(el, _prvi->sljedeci);
    _prvi->sljedeci = newCvor;
    ++velicina;
    _posljednji = newCvor;
    ++duzina_L;
    return;
  }
  Cvor *newCvor = new Cvor(el, (_trenutni->sljedeci)->sljedeci);
  (_trenutni->sljedeci)->sljedeci = newCvor;
  if (_trenutni->sljedeci == _posljednji)
    _posljednji = newCvor;
  ++velicina;
  ++duzina_D;
}

template <typename T> T &JednostrukaLista<T>::operator[](int i) {
  if (i < 0 || i >= velicina) {
    throw std::range_error("Indeks nije validan");
  }

  Cvor *trenutni = _prvi->sljedeci;
  for (int j = 0; j < i; ++j)
    trenutni = trenutni->sljedeci;

  return trenutni->element;
}

template <typename T> T JednostrukaLista<T>::operator[](int i) const {
  if (i < 0 || i >= velicina) {
    throw std::range_error("Indeks nije validan");
  }

  Cvor *trenutni = _prvi->sljedeci;
  for (int j = 0; j < i; ++j)
    trenutni = trenutni->sljedeci;

  return trenutni->element;
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
    std::cout<<"***JEDNOSTRUKA LISTA***\n";
    JednostrukaLista<int> jLista;
    for(int i=0; i<1000; i++) {
        jLista.dodajIza(i);
        jLista.sljedeci();
    }
    brElemenata_test(jLista);
    trenutni_test(jLista);
    prethodni_test(jLista);
    sljedeci_test(jLista);
    pocetak_test(jLista);
    kraj_test(jLista);

    dodajIspred_test(jLista, 42);
    dodajIza_test(jLista, 99);
    std::cout<<"Trenutni element je: "<<jLista[--jLista.trenutni()]<<"\n";
    obrisi_test(jLista);
    std::cout<<"\n***NIZ LISTA***\n";
    NizLista<int> nLista;

    for(int i=0; i<1000; i++) {
        nLista.dodajIza(i);
        nLista.sljedeci();
    }
    brElemenata_test(nLista);
    trenutni_test(nLista);
    prethodni_test(nLista);
    sljedeci_test(nLista);
    pocetak_test(nLista);
    kraj_test(nLista);

    dodajIspred_test(nLista, 77);
    dodajIza_test(nLista, 99);

    std::cout<<"Trenutni element je: "<<nLista[++nLista.trenutni()]<<"\n";

    obrisi_test(nLista);

}