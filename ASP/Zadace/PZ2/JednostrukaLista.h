#pragma once

#include "Lista.h"

template <typename T>
class JednostrukaLista : public Lista<T> {
private:
  struct Cvor {
      T element;
      Cvor *sljedeci;
      Cvor(const T &el, Cvor *sljedeci=nullptr):element(el), sljedeci(sljedeci) {}
      Cvor(Cvor* sljedeci = nullptr):sljedeci(sljedeci) {}
  };
  void ispisiUnazad2(Cvor *sljedeci);
  Cvor *_prvi, *_posljednji, *_trenutni;
  int velicina, duzina_L, duzina_D;

public:
  JednostrukaLista() : _prvi(new Cvor(nullptr)), _posljednji(_prvi), _trenutni(_prvi),
        velicina(0), duzina_D(0), duzina_L(0) {}
  ~JednostrukaLista() {
      while(_prvi != nullptr) {
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
  
  void ispisiUnazad();
};

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
  if (velicina == 0) {    //obrisi || uslov
    _prvi->sljedeci = newCvor;
    _posljednji = newCvor;
  } else {
  _trenutni->sljedeci = newCvor;
  
  
  }
  _trenutni = newCvor;    //vrati u else iznad
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

template <typename T> 
void JednostrukaLista<T>::ispisiUnazad2(Cvor *c) {
  //std::cout<<"\n***POZVAN ispisiUnazad2()***\n";
  if(c == nullptr)
    return;
  
  return ispisiUnazad2(c->sljedeci);
  std::cout<<c->element<<" ";
  
} 

template <typename T> void JednostrukaLista<T>::ispisiUnazad() {
  //std::cout<<"\n***POZVAN ispisiUnazad()***\n";
  ispisiUnazad2(_prvi->sljedeci);
  std::cout<<"\n";
    
  return;  
}