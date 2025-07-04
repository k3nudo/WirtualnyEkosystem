//
// Created by student on 30.04.2025.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "osobniki.h"

#include "srodowisko.h"
#include "nisza.h"
#include "generatorlosowy.h"
#include "ustawienia.h"

srodowisko::srodowisko(unsigned int _wiersze, unsigned int _kolumny)
    : wiersze(_wiersze),
      kolumny(_kolumny),
      liczbaNisz(_wiersze * _kolumny) {
    nisza = new Nisza *[wiersze];
    for (unsigned int i = 0; i < wiersze; i++) {
        nisza[i] = new Nisza[kolumny];
    }
}

srodowisko::~srodowisko() {
    for (unsigned int i = 0; i < wiersze; i++) {
        delete [] nisza[i];
    }
    delete[] nisza;
}

void srodowisko::lokuj(Mieszkaniec *mieszkaniec, unsigned int wiersz, unsigned int kolumna) {
    if (wiersz < wiersze && kolumna < kolumny) {
        nisza[wiersz][kolumna].przyjmijLokatora(mieszkaniec);
    }
}

sasiedztwo srodowisko::ustalSasiedztwo(unsigned int wiersz, unsigned int kolumna) const
{
    sasiedztwo sasiedztwo(SCIANA);

    long wiersz1, kolumna1;

    for(Polozenie p : {P, PG, G, LG, L, LD, D, PD})
    {
        wiersz1 = wiersz;
        kolumna1 = kolumna;

        sasiedztwo::zmienIdeksyWgPolozenia(p, wiersz1, kolumna1);

        if(wiersz1 >= 0 &&
           wiersz1 < wiersze &&
           kolumna1 >= 0 &&
           kolumna1 < kolumny)
        {
            sasiedztwo.okreslSasiada(p,
                nisza[wiersz1][kolumna1].ktoTuMieszka());
        }
    }

    return sasiedztwo;
}

unsigned long srodowisko::liczba(RodzajMieszkanca rodzaj) const
{
    unsigned long licznik = 0;

    for(unsigned int w = 0; w < wiersze; w++)
        for(unsigned int k = 0; k < kolumny; k++)
            if(nisza[w][k].ktoTuMieszka() == rodzaj)
                licznik++;

    return licznik;
}

bool srodowisko::martwy()
{
    return liczba(GLON) + liczba(GRZYB) + liczba(BAKTERIA) == 0;
}

void srodowisko::wykonajSkok(unsigned int wiersz,unsigned int kolumna)
{
    if(!nisza[wiersz][kolumna].lokatorZywy() ||
       nisza[wiersz][kolumna].ktoTuMieszka() == GLON) return;

    sasiedztwo sasiedztwo = ustalSasiedztwo(wiersz, kolumna);

    if(sasiedztwo.ile(PUSTKA) > 0){
        Polozenie polozenie = sasiedztwo.losujSasiada(PUSTKA);

        unsigned int wiersz1 = wiersz, kolumna1 = kolumna;

        sasiedztwo::zmienIdeksyWgPolozenia(polozenie,wiersz1, kolumna1);

        nisza[wiersz1][kolumna1] = nisza[wiersz][kolumna];
    }
}

void srodowisko::wykonajAkcje(unsigned int wiersz,
                               unsigned int kolumna)
{
    if(!nisza[wiersz][kolumna].lokatorZywy()) return;

    sasiedztwo sasiedztwo = ustalSasiedztwo(wiersz, kolumna);

    ZamiarMieszkanca zamiar =
        nisza[wiersz][kolumna].aktywujLokatora(sasiedztwo);

    unsigned int wiersz1 = wiersz, kolumna1 = kolumna;

    sasiedztwo::zmienIdeksyWgPolozenia(zamiar.gdzie,
                                       wiersz1, kolumna1);

    Mieszkaniec* m = nullptr;

    switch (zamiar.akcja) {
        case NIC:
            wykonajSkok(wiersz, kolumna);
        break;

        case POTOMEK:
            m = nisza[wiersz][kolumna].wypuscPotomka();
        nisza[wiersz1][kolumna1].przyjmijLokatora(m);
        break;

        case POLOWANIE:
        case ROZKLAD:
            m = nisza[wiersz1][kolumna1].oddajLokatora();
        nisza[wiersz][kolumna].przyjmijZdobycz(m);
        break;
    }
}

void srodowisko::wykonajKrokSymulacji()
{
    WektorIndeksow2D indeksyLosowe =
        GeneratorLosowy::indeksyLosowe(wiersze, kolumny);

    for(Indeks2D indeks : indeksyLosowe)
        wykonajAkcje(indeks.wiersz, indeks.kolumna);
}

string srodowisko::doTekstu() const
{
    string tekst = "";
    char sep = UstawieniaSymulacji::pobierzUstawienia().znakSeparator;

    for(unsigned int w = 0; w < wiersze; w++) {
        for(unsigned int k = 0; k < kolumny; k++) {
            if(k > 0) tekst += sep;
            tekst += nisza[w][k].jakiSymbol();
        }
        tekst += '\n';
    }

    tekst += "\n Glony * : " + to_string(liczba(GLON))
          + "\n Grzyby # : " + to_string(liczba(GRZYB))
          + "\nBakterie @ : " + to_string(liczba(BAKTERIA))
          + "\n Martwe + : " + to_string(liczba(TRUP))
          + '\n';

    return tekst;
}

ostream &operator<<(ostream &strumien, const srodowisko &srodowisko)
{
    strumien << srodowisko.doTekstu();
    return strumien;
}

srodowisko srodowisko::czytajZPliku(string nazwaPliku) {
    ifstream plik(nazwaPliku);
    stringstream tekst("");

    if (plik) {
        tekst << plik.rdbuf();
        plik.close();
    }

    string zapis = tekst.str();
    unsigned int wiersze = 0, kolumny = 0;
    bool pierwszaLinia = true;

    for (char c : zapis) {
        if (c != '\n') {
            if (pierwszaLinia && c != ' ') kolumny++;
        } else {
            pierwszaLinia = false;
            wiersze++;
        }
    }

    srodowisko srodowisko(wiersze, kolumny);

    char glon = UstawieniaSymulacji::pobierzUstawienia().znakGlon;
    char grzyb = UstawieniaSymulacji::pobierzUstawienia().znakGrzyb;
    char bakteria = UstawieniaSymulacji::pobierzUstawienia().znakBakteria;
    char pusta = UstawieniaSymulacji::pobierzUstawienia().znakPustaNisza;

    char znak;
    for (unsigned int w = 0; w < wiersze; w++) {
        getline(tekst, zapis);
        for (unsigned int k = 0; k < 2 * kolumny; k += 2) {
            znak = k < zapis.size() ? zapis[k] : pusta;

            if (znak == glon)
                srodowisko.lokuj(new Glon(), w, k / 2);
            else if (znak == grzyb)
                srodowisko.lokuj(new Grzyb(), w, k / 2);
            else if (znak == bakteria)
                srodowisko.lokuj(new Bakteria(), w, k / 2);
        }
    }

    return srodowisko;
}
