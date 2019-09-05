#ifndef IRANDOMNUMBERSGENERATOR_H
#define IRANDOMNUMBERSGENERATOR_H

#include <random>

class IRandomNumbersGenerator
{
public:
    virtual ~IRandomNumbersGenerator() {}

    virtual double GenerateRandomValue
    (std::uniform_real_distribution<> &dist) = 0;
};

#endif // IRANDOMNUMBERSGENERATOR_H
