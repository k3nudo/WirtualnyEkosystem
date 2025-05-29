#include <iostream>
#include "nisza.h"
#include "osobniki.h"

using namespace std;

//globalne nisze oraz separator
static Nisza n1, n2, n3;
static char sep = UstawieniaSymulacji::pobierzUstawienia().znakSeparator;

void wyswietlNisze() {
    cout << n1.jakiSymbol() << sep
            << n2.jakiSymbol() << sep
            << n3.jakiSymbol() << endl;
}

int main() {
    cout << "Puste nisze: ";
    wyswietlNisze();

    cout << "Lokowanie mieszkancow: ";
    n1.przyjmijLokatora(new Glon());
    n3.przyjmijLokatora(new Grzyb());
    wyswietlNisze();

    cout << "Przesuwanie lokatorow: ";
    n2 = n1;
    wyswietlNisze();

    cout << "Przesuwanie lokatorow: ";
    n3 = n2;
    wyswietlNisze();

    cout << endl;
    return 0;
}
