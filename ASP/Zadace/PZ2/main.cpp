#include <bits/stdc++.h>
template <typename T> class Lista {

public:
  Lista() {}
  virtual int brojElemenata() const = 0;
  virtual T &trenutni() = 0;
  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  virtual void dodajIspred(const T &el) = 0;
  virtual void dodajIza(const T &el) = 0;
  virtual T &operator[](int i) = 0;
};

template <typename T> class NizLista : public Lista<T> {
  int velicina, kapacitet;
  T *lista;
  int _trenutni, _pocetak, _kraj;

public:
  NizLista()
      : velicina(0), kapacitet(100), lista(new T[kapacitet]), _trenutni(-1),
        _pocetak(-1), _kraj(-1) {}

  NizLista(const NizLista<T>& l) {
      velicina = l.velicina;
      kapacitet = l.kapacitet;
      lista = new T[kapacitet];
      for(int i=0; i<l.brojElemenata(); i++)
        lista[i] = l.lista[i];
      _trenutni = l._trenutni;
      _pocetak = l._pocetak;
      _kraj = l._kraj;
  }

  void operator=(const NizLista<T>& l) {
    velicina = l.velicina;
    kapacitet = l.kapacitet;
    delete[] lista;
    lista = new T[kapacitet];
    for(int i=0; i<l.brojElemenata(); i++)
        lista[i] = l.lista[i];
    _trenutni = l._trenutni;
    _pocetak = l._pocetak;
    _kraj = l._kraj;
  }

  int brojElemenata() const override { return velicina; }

  T &trenutni() override { return lista[_trenutni]; }
  T trenutni() const { return lista[_trenutni]; }

  bool prethodni() override {
    if (_trenutni > 0) {
      --_trenutni;
      return true;
    }
    return false;
  }

  bool sljedeci() override {
    if (_trenutni != _kraj) {
      ++_trenutni;
      return true;
    }
    return false;
  }

  void pocetak() override { _trenutni = _pocetak; }

  void kraj() override { _trenutni = _kraj; }

  void obrisi() override {
    if (velicina == 0)
      return;
    if (_trenutni == _kraj) {
      --_trenutni;
      --velicina;
      return;
    }
    for (int i = _trenutni; i < _kraj - 1; i++)
      lista[i] = lista[i + 1];
    --velicina;
    ++_trenutni;
  }

  void dodajIspred(const T &el) override {
    if (velicina == 0) {
      lista[0] = el;
      _trenutni = 0;
      ++velicina;
      _pocetak = _kraj = _trenutni;
      return;
    } else if (velicina == kapacitet) {
      kapacitet *= 2;

      T *novaLista = new T[kapacitet];
      for (int i = 0; i < velicina; ++i)
        novaLista[i] = lista[i];

      delete[] lista;
      lista = novaLista;
    }
    ++_kraj;
    for (int i = _kraj; i > _trenutni; --i)
      lista[i] = lista[i - 1];

    lista[_trenutni] = el;
    ++_trenutni;
    ++velicina;
    
  }

  void dodajIza(const T &el) override {
    if (velicina == 0) {
      lista[0] = el;
      _trenutni = 0;
      ++velicina;
      _pocetak = _kraj = _trenutni;
      return;
    } else if (velicina == kapacitet) {
      kapacitet *= 2;
      T *novaLista = new T[kapacitet];

      for (int i = 0; i < velicina; ++i)
        novaLista[i] = lista[i];
      delete[] lista;
      lista = novaLista;
    }
    ++_kraj;
    for (int i = _kraj; i > _trenutni + 1; --i)
      lista[i] = lista[i - 1];
    lista[_trenutni + 1] = el;
    ++velicina;
  }

  T &operator[](int i) override {
    if (i >= 0 && i <= velicina) {
      return lista[i];
    }
    throw std::range_error("Indeks nije validan");
  }

  T &operator[](int i) const {
      if (i >= 0 && i <= velicina) {
      return lista[i];
    }
    throw std::range_error("Indeks nije validan");
  }

  ~NizLista() { delete[] lista; }
};

template <typename T> class cvor {
public:
  T *podaci;
  cvor<T> *next;

  cvor(const T &value) : podaci(new T(value)), next(nullptr) {}
  ~cvor() { delete podaci; }
};

template <typename T> class JednostrukaLista : public Lista<T> {

    /**
    *
    *   TODO: dodati konstantne verzije operatora [] i trenutni();
    *
    */

private:
  cvor<T> *_pocetak;
  cvor<T> *_trenutni;
  int velicina;

public:
  JednostrukaLista() : _pocetak(nullptr), _trenutni(nullptr), velicina(0) {}

  int brojElemenata() const override { return velicina; }

  T &trenutni() override {
    if (_trenutni != nullptr) {
      return *(_trenutni->podaci);
    } else {
      throw std::out_of_range("Current is nullptr.");
    }
  }

  bool prethodni() override {
    if (_trenutni == nullptr || _trenutni == _pocetak) {
      return false;
    } else {
      cvor<T> *temp = _pocetak;
      while (temp->next != _trenutni) {
        temp = temp->next;
      }
      _trenutni = temp;
      return true;
    }
  }

  bool sljedeci() override {
    if (_trenutni != nullptr && _trenutni->next != nullptr) {
      _trenutni = _trenutni->next;
      return true;
    } else {
      return false;
    }
  }

  void pocetak() override { _trenutni = _pocetak; }

  void kraj() override {
    if (_pocetak == nullptr) {
      _trenutni = nullptr;
    } else {
      while (_trenutni->next != nullptr) {
        _trenutni = _trenutni->next;
      }
    }
  }

  void obrisi() override {
    if (_trenutni != nullptr) {
      if (_trenutni == _pocetak) {
        _pocetak = _pocetak->next;
        delete _trenutni;
        _trenutni = _pocetak;
      } else {
        cvor<T> *temp = _pocetak;
        while (temp->next != _trenutni) {
          temp = temp->next;
        }
        temp->next = _trenutni->next;
        delete _trenutni;
        _trenutni = temp->next;
      }
      velicina--;
    }
  }

  void dodajIspred(const T &el) override {
    cvor<T> *newcvor = new cvor<T>(el);
    if (_trenutni != nullptr) {
      if (_trenutni == _pocetak) {
        newcvor->next = _pocetak;
        _pocetak = newcvor;
      } else {
        cvor<T> *temp = _pocetak;
        while (temp->next != _trenutni) {
          temp = temp->next;
        }
        temp->next = newcvor;
        newcvor->next = _trenutni;
      }
      velicina++;
    } else {
      // If the list is empty, add the element as the only cvor.
      _pocetak = newcvor;
      _trenutni = newcvor;
      velicina++;
    }
  }

  void dodajIza(const T &el) override {
    cvor<T> *newcvor = new cvor<T>(el);
    if (_trenutni != nullptr) {
      newcvor->next = _trenutni->next;
      _trenutni->next = newcvor;
      velicina++;
    } else {
      // If the list is empty, add the element as the only cvor.
      _pocetak = newcvor;
      _trenutni = newcvor;
      velicina++;
    }
  }

  T &operator[](int i) override {
    if (i < 0 || i >= velicina) {
      throw std::out_of_range("Index out of bounds.");
    }

    cvor<T> *temp = _pocetak;
    for (int j = 0; j < i; ++j) {
      temp = temp->next;
    }

    return *(temp->podaci);
  }

};



int main() {
    Lista<int>* l = new NizLista<int>;
    std::cout<<"\nKREIRAO NizListu!\n";
    for (int i = 0; i < 100000; i++)
    l->dodajIza(5);

    std::cout << "\nDODAO\n";

    try {
        std::cout << "\nCurrent element: " << l->trenutni() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    for (int i = 0; i < 13; i++) {
        std::cout<<l->trenutni()<<" ";
        l->sljedeci();
    }

    delete l;
    return 0;
}