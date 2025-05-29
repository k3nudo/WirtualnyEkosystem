#include <iostream>
#include "nisza.h"
#include "osobniki.h"
#include "sasiedztwo.h"

using namespace std;


int main() {
    Nisza nisza;
    nisza.przyjmijLokatora(new Bakteria());

    cout << "Kto w niszy: "
            << nisza.ktoTuMieszka() << endl;
    cout << "Czy zywy: "
            << nisza.lokatorZywy() << endl;

    sasiedztwo sasiedztwo;

    sasiedztwo.okreslSasiada(P, GLON);
    sasiedztwo.okreslSasiada(PG, GRZYB);
    sasiedztwo.okreslSasiada(G, GRZYB);
    sasiedztwo.okreslSasiada(LG, GLON);
    sasiedztwo.okreslSasiada(L, BAKTERIA);
    sasiedztwo.okreslSasiada(LD, BAKTERIA);
    sasiedztwo.okreslSasiada(D, GLON);
    sasiedztwo.okreslSasiada(PD, PUSTKA);

    ZamiarMieszkanca zamiar = nisza.aktywujLokatora(sasiedztwo);

    cout << "Akcja: " << zamiar.akcja << " gdzie: " << zamiar.gdzie << endl;
    cout << endl;

    return 0;


    return 0;
}
