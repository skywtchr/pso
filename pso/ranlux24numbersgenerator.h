#ifndef RANDOMNUMBERSGENERATOR_H
#define RANDOMNUMBERSGENERATOR_H

#include <random>
#include <ctime>

#include "irandomnumbersgenerator.h"

class Ranlux24NumbersGenerator : public IRandomNumbersGenerator
{
public:
    Ranlux24NumbersGenerator();
    ~Ranlux24NumbersGenerator();

    double GenerateRandomValue(std::uniform_real_distribution<> &dist);

private:
    std::ranlux24_base* _randomNumbersEngine;
};

#endif // RANDOMNUMBERSGENERATOR_H
