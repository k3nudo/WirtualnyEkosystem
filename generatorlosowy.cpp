//
// Created by student on 30.04.2025.
//

#include "generatorlosowy.h"
#include <algorithm>
using namespace std;

random_device GeneratorLosowy::device; //definicja device

unsigned short GEN::losujPomiedzy(unsigned short min, unsigned short max)
{
    if (min > max) {
        unsigned short t = min;
        min = max;
        max = t;
    }

    uniform_int_distribution<unsigned short> dist(min, max);
    return dist(GeneratorLosowy::device);
}

long GeneratorLosowy::losujPomiedzy(long min, long max)
{
    if (min > max) {
        long t = min;
        min = max;
        max = t;
    }

    uniform_int_distribution<long> dist(min, max);
    return dist(GeneratorLosowy::device);
}

int GeneratorLosowy::losujOdZeraDo(int max)
{
    uniform_int_distribution<int> dist(0, max);
    return dist(GeneratorLosowy::device);
}

WektorIndeksow2D GeneratorLosowy::indeksyLosowe(unsigned int wiersze, unsigned int kolumny)
{
    WektorIndeksow2D indeksy;

    for(unsigned int w = 0; w < wiersze; w++)
        for(unsigned int k = 0; k < kolumny; k++)
            indeksy.push_back(Indeks2D(w, k));

    std::random_shuffle(indeksy.begin(), indeksy.end(), GeneratorLosowy::losujOdZeraDo);

    return indeksy;
}
