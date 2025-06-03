#include <iostream>
#include "nisza.h"
#include "osobniki.h"
#include "sasiedztwo.h"
#include <fstream>

using namespace std;

int main()
{
    srodowisko ekoSystem(8, 12);

    ekoSystem.lokuj(new Glon(), 0, 10);
    ekoSystem.lokuj(new Glon(), 1, 10);
    ekoSystem.lokuj(new Glon(), 1, 13);
    ekoSystem.lokuj(new Glon(), 3, 10);
    ekoSystem.lokuj(new Grzyb(), 1, 11);
    ekoSystem.lokuj(new Grzyb(), 0, 0);
    ekoSystem.lokuj(new Bakteria(), 3, 3);
    ekoSystem.lokuj(new Bakteria(), 2, 6);

    ofstream plikWynikowy("symulacja.txt");
    if (!plikWynikowy.is_open()) return 1;
    string stanSymulacji;

    unsigned long i = 0;

    do {
        system("clear");
        cout << "Krok symulacji: " << i << endl;
        plikWynikowy << "Krok symulacji: " << i << endl;
        stanSymulacji = ekoSystem.doTekstu();

        cout << endl << stanSymulacji << endl;
        plikWynikowy << stanSymulacji << endl;
        cin.ignore(1);
        ekoSystem++;
        i++;
    } while (i < 200 && !ekoSystem);

    cout << endl;

    plikWynikowy.close();
    return 0;
}
