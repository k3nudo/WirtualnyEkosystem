//
// Created by student on 30.04.2025.
//

#include "osobniki.h"

Glon::Glon():
    Organizm(GeneratorLosowy::losujPomiedzy(UST.glonZycieMin, UST.glonZycieMax),
             UST.glonLimitPosilkow, UST.glonKosztPotomka),
    Mieszkaniec(UST.znakGlon) {}

Grzyb::Grzyb():
    Organizm(GeneratorLosowy::losujPomiedzy(UST.grzybZycieMin, UST.grzybZycieMax),
             UST.grzybLimitPosilkow, UST.grzybKosztPotomka),
    Mieszkaniec(UST.znakGrzyb) {}

Bakteria::Bakteria():
    Organizm(GeneratorLosowy::losujPomiedzy(UST.bakteriaZycieMin, UST.bakteriaZycieMax),
             UST.bakteriaLimitPosilkow, UST.bakteriaKosztPotomka),
    Mieszkaniec(UST.znakBakteria) {}

RodzajMieszkanca Glon::kimJestes() {
    return zywy() ? GLON : TRUP;
}

RodzajMieszkanca Grzyb::kimJestes() {
    return zywy() > 0 ? GRZYB : TRUP;
}

RodzajMieszkanca Bakteria::kimJestes() {
    return zywy() ? BAKTERIA : TRUP;
}

Mieszkaniec * Glon::dajPotomka() {
    Mieszkaniec * m = nullptr;
    if (potomek()) m = new Glon();
    return m;
}

Mieszkaniec * Grzyb::dajPotomka() {
    Mieszkaniec * m = nullptr;
    if (potomek()) m = new Grzyb();
    return m;
}

Mieszkaniec * Bakteria::dajPotomka() {
    Mieszkaniec * m = nullptr;
    if (potomek()) m = new Bakteria();
    return m;
}

void Glon::przyjmijZdobycz(Mieszkaniec * mieszkaniec) {
    if (mieszkaniec != nullptr) delete mieszkaniec;
}

void Grzyb::przyjmijZdobycz(Mieszkaniec * mieszkaniec) {
    if (mieszkaniec != nullptr) {
        if (mieszkaniec->kimJestes() == TRUP) posilek();
        delete mieszkaniec;
    }
}

void Bakteria::przyjmijZdobycz(Mieszkaniec * mieszkaniec) {
    if (mieszkaniec != nullptr) {
        RodzajMieszkanca r = mieszkaniec->kimJestes();
        if (r == GLON || r == GRZYB) posilek();
        delete mieszkaniec;
    }
}

ZamiarMieszkanca Glon::wybierzAkcje(sasiedztwo sasiedztwo) {
    krokSymulacji();

    if (zywy() && paczkujacy() && sasiedztwo.ile(PUSTKA) > 0)
        return ZamiarMieszkanca(POTOMEK, sasiedztwo.losujSasiada(PUSTKA));

    if (zywy() && glodny()) posilek();

    if (!zywy() && symbol != UST.znakTrup)
        symbol = UST.znakTrup;

    return ZamiarMieszkanca();
}

ZamiarMieszkanca Grzyb::wybierzAkcje(sasiedztwo sasiedztwo) {
    krokSymulacji();

    if (zywy() && paczkujacy() && sasiedztwo.ile(PUSTKA) > 0)
        return ZamiarMieszkanca(POTOMEK, sasiedztwo.losujSasiada(PUSTKA));

    if (zywy() && glodny() && sasiedztwo.ile(TRUP) > 0)
        return ZamiarMieszkanca(ROZKLAD, sasiedztwo.losujSasiada(TRUP));

    if (!zywy() && symbol != UST.znakTrup)
        symbol = UST.znakTrup;

    return ZamiarMieszkanca();
}

ZamiarMieszkanca Bakteria::wybierzAkcje(sasiedztwo sasiedztwo) {
    krokSymulacji();

    if (zywy() && paczkujacy() && sasiedztwo.ile(PUSTKA) > 0)
        return ZamiarMieszkanca(POTOMEK, sasiedztwo.losujSasiada(PUSTKA));

    if (zywy() && glodny() && sasiedztwo.ile(GLON) > 0)
        return ZamiarMieszkanca(POLOWANIE, sasiedztwo.losujSasiada(GLON));

    if (zywy() && glodny() && sasiedztwo.ile(BAKTERIA) > 0)
        return ZamiarMieszkanca(POLOWANIE, sasiedztwo.losujSasiada(BAKTERIA));

    if (!zywy() && symbol != UST.znakTrup)
        symbol = UST.znakTrup;

    return ZamiarMieszkanca();
}


