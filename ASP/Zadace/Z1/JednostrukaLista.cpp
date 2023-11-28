#include <iostream>
#include <stdexcept>
/**
 * @brief Apstraktna klasa Lista, iz koje su izvedene JednostrukaLista,
 * DvostrukaLista i NizLista
 * 
 * @tparam T - bilo koji POD tip podatka koji ce vaziti za elemente liste
 */
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
            : element(el), sljedeci(sljedeci), prethodni(prethodni) {}

        Cvor(Cvor *sljedeci = nullptr, *prethodni=nullptr) 
            : sljedeci(sljedeci), prethodni(prethodni) {}
    };
    
    Cvor *_prvi, *_posljednji, *_trenutni;
    int velicina, duzina_D, duzina_L;

public:
    DvostrukaLista()
        : _prvi(new Cvor(nullptr)), _posljednji(_prvi), _trenutni(_prvi),
        velicina(0), duzina_D(0), duzina_L(0) {}

    ~DvostrukaLista() {
        while (_prvi != nullptr) {
        Cvor *temp = _prvi;
        _prvi = _prvi->sljedeci;
        delete temp;
        }
    }
    
    DvostrukaLista(const DvostrukaLista<T> &jl);
    DvostrukaLista<T> &operator=(const DvostrukaLista<T> &jl);
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