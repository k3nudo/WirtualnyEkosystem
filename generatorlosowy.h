//
// Created by student on 30.04.2025.
//

#ifndef GENERATORLOSOWY_H
#define GENERATORLOSOWY_H
#include <random>
using namespace std;

class Indeks2D {
public:
    unsigned int wiersz, kolumna;
    Indeks2D(unsigned int _w=0, unsigned int _k=0):
    wiersz(_w),kolumna(_k){}
};

typedef vector<Indeks2D> WektorIndeksow2D;

class GeneratorLosowy
{
private:
    static random_device device; //deklaracja device
    GeneratorLosowy() {}

public:
    static unsigned short losujPomiedzy(unsigned short min, unsigned short max);
    static long losujPomiedzy(long min, long max);
    static int losujOdZeraDo(int max);
    static WektorIndeksow2D indeksyLosowe(unsigned int wiersze,unsigned int kolumny);
};

typedef GeneratorLosowy GEN;



#endif //GENERATORLOSOWY_H
