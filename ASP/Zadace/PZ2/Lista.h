#pragma once

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
