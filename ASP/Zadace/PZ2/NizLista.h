#pragma once
#include "Lista.h"


template <typename T> class NizLista : public Lista<T> {
  T **lista;
  int velicina, kapacitet;
  int _trenutni, _kraj;
  void realloc();

public:
  NizLista()
      : velicina(0), kapacitet(100), _trenutni(-1), _kraj(-1) {
    lista = new T *[kapacitet];
  }

  ~NizLista() {
    for (int i = 0; i < velicina; i++)
      delete[] lista[i];
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

template <typename T>
  void NizLista<T>::realloc() {
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

  template <typename T>
  T &NizLista<T>::trenutni() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    return *(lista[_trenutni]);
  }
  template <typename T>
  T NizLista<T>::trenutni() const {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    return *(lista[_trenutni]);
  }
  template <typename T>
  bool NizLista<T>::prethodni() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    if (_trenutni > 0) {
      --_trenutni;
      return true;
    }
    return false;
  }

  template <typename T>
  bool NizLista<T>::sljedeci() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    if (_trenutni != _kraj) {
      ++_trenutni;
      return true;
    }
    return false;
  }
  template <typename T>
  void NizLista<T>::pocetak() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    _trenutni = 0;
  }

  template <typename T>
  void NizLista<T>::kraj() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    _trenutni = _kraj;
  }

  template <typename T>
  void NizLista<T>::obrisi() {
    if (this->velicina == 0)
      throw std::logic_error("Lista je prazna!");
    delete lista[_trenutni];
    for (int i = _trenutni; i < _kraj - 1; i++)
      lista[i] = lista[i + 1];
    lista[_trenutni - 1] = nullptr;
    if (_trenutni == velicina - 1 && _trenutni != 0)
      --_trenutni;
    --velicina;
  }

  template <typename T>
  void NizLista<T>::dodajIspred(const T &el) {
    if (velicina >= kapacitet)  //kada ima potreba za realokacijom
      this->realloc();
    if (velicina == 0) {        //prvi element
      lista[0] = new T(el);
      _trenutni = 0;
      _kraj = _trenutni;
      ++velicina;
      return;
    }
    //dodavanje ako nije specijalni slucaj:
    ++_kraj;
    for (int i = _kraj; i > _trenutni; --i)
      lista[i] = lista[i-1];
    lista[_trenutni] = new T(el);
    ++_trenutni;
    ++velicina;
  }

  template <typename T>
  void NizLista<T>::dodajIza(const T &el) {
    if(velicina >= kapacitet)   //kada ima porebe za realokacijom
      this->realloc();
    if (velicina == 0) {        //prvi element
      lista[0] = new T(el);
      _trenutni = 0;
      _kraj = _trenutni;
      ++velicina;
      return;
    } 
    //dodavanje ako nije specijalan slucaj:
    ++_kraj;
    for (int i=_kraj; i>_trenutni+1; --i)
      lista[i] = lista[i-1];
    lista[_trenutni+1] = new T(el);
    ++velicina;
  }
  template <typename T>
  T &NizLista<T>::operator[](int i) {
    if (i >= 0 && i <= velicina) {
      return *(lista[i]);
    }
    throw std::range_error("Indeks nije validan");
  }

  template <typename T>
  T NizLista<T>::operator[](int i) const {
    if (i >= 0 && i <= velicina) {
      return *(lista[i]);
    }
    throw std::range_error("Indeks nije validan");
  }