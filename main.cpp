#include <iostream>
#include "Organizm.h"
#include "ustawienia.h"
#include "generatorlosowy.h"

using namespace std;

int main()
{
    cout << "Liczby losowe typu int:" << endl;
    cout << " od 0 do 5: ";
    for (int i = 0; i < 10; i++)
        cout << GEN::losujOdZeraDo(5) << " ";

    cout << endl << " od 0 do 3: ";
    for (int i = 0; i < 10; i++)
        cout << GEN::losujOdZeraDo(3) << " ";

    cout << endl << " od 0 do 20: ";
    for (int i = 0; i < 10; i++)
        cout << GEN::losujOdZeraDo(20) << " ";

    cout << endl << endl;

    cout << "Liczby losowe typu long: " << endl;
    cout << " od -2 do 2: ";
    for (int i = 0; i < 10; i++)
        cout << GEN::losujPomiedzy(-2L, 2L) << " ";

    cout << endl << endl
         << "Liczby losowe typu unsigned short: " << endl;
    cout << " od 2 do 6: ";
    unsigned short min = 2, max = 6;

    for (int i = 0; i < 10; i++)
        cout << GEN::losujPomiedzy(max, min) << " ";

    cout << endl << endl;

    return 0;
}