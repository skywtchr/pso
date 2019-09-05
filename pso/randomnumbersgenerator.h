#ifndef RANDOMNUMBERSGENERATOR_H
#define RANDOMNUMBERSGENERATOR_H

#include <random>
#include <ctime>

class RandomNumbersGenerator
{
public:
    RandomNumbersGenerator();
    ~RandomNumbersGenerator();

    double GenerateRandomValue(std::uniform_real_distribution<> &dist);

private:
    std::ranlux24_base* _randomNumbersEngine;
};

#endif // RANDOMNUMBERSGENERATOR_H
