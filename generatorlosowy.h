//
// Created by student on 30.04.2025.
//

#ifndef GENERATORLOSOWY_H
#define GENERATORLOSOWY_H
#include <random>
using namespace std;

class GeneratorLosowy
{
private:
    static random_device device; //deklaracja device
    GeneratorLosowy() {}

public:
    static unsigned short losujPomiedzy(unsigned short min, unsigned short max);
    static long losujPomiedzy(long min, long max);
    static int losujOdZeraDo(int max);
};

typedef GeneratorLosowy GEN;



#endif //GENERATORLOSOWY_H
