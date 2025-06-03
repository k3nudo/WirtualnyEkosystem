//
// Created by student on 30.04.2025.
//

#ifndef SRODOWISKO_H
#define SRODOWISKO_H

#include <string>
#include "ustawienia.h"

class Nisza;
class Mieszkaniec;
class sasiedztwo;


class srodowisko {
public:
    const unsigned int wiersze,kolumny;
    const unsigned int long liczbaNisz;

private:
    Nisza ** nisza;

public:
    srodowisko(unsigned int _wiersze, unsigned int _kolumny);

    ~srodowisko();

    void lokuj(Mieszkaniec * mieszkaniec,unsigned int wiersz, unsigned int kolumna);

    sasiedztwo ustalSasiedztwo(unsigned int wiersz, unsigned int kolumna) const;

    unsigned long liczba(RodzajMieszkanca rodzaj) const;

    bool martwy();

    void wykonajSkok(unsigned int wiersz, unsigned int kolumna);

    void wykonajAkcje(unsigned int wiersz, unsigned int kolumna);

    void wykonajKrokSymulacji();

    std::string doTekstu() const;

    void operator++(int) { wykonajKrokSymulacji(); }

    bool operator!() { return !martwy(); }

};

std::ostream &operator<<(std::ostream &strumien, const srodowisko &srodowisko);



#endif //SRODOWISKO_H
