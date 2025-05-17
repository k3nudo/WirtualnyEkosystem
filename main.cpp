#include <iostream>
#include "Organizm.h"
#include "ustawienia.h"
#include "generatorlosowy.h"
using namespace std;

void drukujOrganizm(const Organizm& o) {
    cout << "licznikZycia: "
         << o.stanLicznikaZycia()
         << " licznikPosilkow: "
         << o.stanLicznikaPosilkow() << endl
         << "limitPosilkow: "
         << o.limitPosilkow
         << " kosztPotomka: "
         << o.kosztPotomka << endl
         << "glodny: " << o.glodny()
         << " paczkujacy: "
         << o.paczkujacy() << endl << endl;
}



int main() {


    Organizm organizm1(8, 3, 2);
    Organizm organizm2 = organizm1;
    Organizm organizm3(organizm1);
    cout << "Wynik testu kreacji obiektow:" << endl << endl;
    cout << "Organizm1:" << endl;
    drukujOrganizm(organizm1);
    cout << "Organizm2:" << endl;
    drukujOrganizm(organizm2);
    cout << "Organizm3:" << endl;
    drukujOrganizm(organizm3);
    organizm1.posilek();
    organizm1.posilek();
    organizm2.posilek();
    organizm3.krokSymulacji();
    cout << "Wynik testu niezaleznosci obiektow:" << endl << endl;
    cout << "Organizm1:" << endl;
    drukujOrganizm(organizm1);
    cout << "Organizm2:" << endl;
    drukujOrganizm(organizm2);
    cout << "Organizm3:" << endl;
    drukujOrganizm(organizm3);
    Organizm organizm4(8, 3, 2);
    cout << "Wynik testu symulacji:" << endl << endl;
    cout << "Stan poczatkowy:" << endl;
    drukujOrganizm(organizm4);
    for (int i = 1; i <= 10; i++) {
        organizm4.krokSymulacji();
        if (organizm4.paczkujacy()) {
            organizm4.potomek();  // Tworzenie potomka
            cout << "---> Potomek" << endl;
        } else {
            organizm4.posilek();  // Jeśli nie, organizm dostaje posiłek
        }
        cout << "Po wykonaniu kroku symulacji: " << i << endl;
        drukujOrganizm(organizm4);
    }


    return 0;
}
