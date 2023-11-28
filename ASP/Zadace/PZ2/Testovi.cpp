#include <iostream>
#include <stdexcept>
#include <ctime>

#include "Lista.h"
#include "NizLista.h"
#include "JednostrukaLista.h"

template <typename T> void brElemenata_test(Lista<T> &l) {
    std::cout<<"\nBroj elemenata je: "<<l.brojElemenata()<<"\n";
}

template <typename T> void trenutni_test(Lista<T> &l) {
    try {
        std::cout<<"Trenutni element je: "<<l.trenutni()<<"\n";
        std::cout<<"\nUmanjen za 1: "<<l.trenutni()--<<"\n";
    } catch (std::exception &e) {
        std::cout<<"\n***IZUZETAK: "<<e.what()<<"\n";
    }
}


template <typename T> void prethodni_test(Lista<T> &l) {
    if(l.prethodni()) std::cout<<"prethodni() uspjesan!\n";
    std::cout<<"prethodni neuspjesan.\n";
}

template <typename T> void sljedeci_test(Lista<T> &l) {
    if(l.prethodni()) std::cout<<"sljedeci() uspjesan!\n";
    std::cout<<"sljedeci() neuspjesan.\n";
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
/*
template <typename T, typename T2> 
void dodajIspred_test(Lista<T> &l, T el) {
    l.dodajIspred(el); 
    std::cout<<el<<" uspjesno dodanIspred()!\n";
}
*/

template <typename TipEl, typename Tip>
void TestDodajIspred(Lista<TipEl> &l, Tip element) {
    l.dodajIspred(element);
    std::cout << element << " dodan ispred trenutnog\n";
}

template <typename T, typename T_el> 
void dodajIza_test(Lista<T> &l, T_el el) {
    l.dodajIza(el); 
    std::cout<<el<<" uspjesno dodanIza()!\n";
}

template <typename T> void obrisi_test(Lista<T> &l) {
    l.obrisi();
    std::cout<<"obrisi() uspjesno izvrsen.\n";
}

template <typename T>
void printList(JednostrukaLista<T>& lista) {
  for (int i = 0; i < lista.brojElemenata(); i++) {
    std::cout << lista[i] << " ";
    //lista.sljedeci();
  }

  std::cout << "\n";

  lista.ispisiUnazad();
}

int main() {
    
    JednostrukaLista<int> jLista;
    
    for(int i=0; i<10; i++) {
        jLista.dodajIspred(i);
        jLista.sljedeci();
    }

    
    brElemenata_test(jLista);
    for (int i = 0; i < jLista.brojElemenata(); i++)
        std::cout << jLista[i] << " ";
    jLista.ispisiUnazad();
    /*
    trenutni_test(jLista);
    prethodni_test(jLista);
    sljedeci_test(jLista);
    pocetak_test(jLista);
    kraj_test(jLista);

   // dodajIspred_test(jLista, 42);
    dodajIza_test(jLista, 99);

    //dodajIspred_test(jLista, "Hello");
    dodajIza_test(jLista, 3.14);

    
    obrisi_test(jLista);

    NizLista<int> nLista;
    for(int i=0; i<10; i++)
        nLista.dodajIza(i);
    brElemenata_test(nLista);
    trenutni_test(nLista);
    prethodni_test(nLista);
    sljedeci_test(nLista);
    pocetak_test(nLista);
    kraj_test(nLista);

    //dodajIspred_test(nLista, 42);
    dodajIza_test(nLista, 99);

    //dodajIspred_test(nLista, "Hello");
    dodajIza_test(nLista, 3.14);

    obrisi_test(nLista);
    */

   //jLista.ispisiUnazad();


    return 0;
}

