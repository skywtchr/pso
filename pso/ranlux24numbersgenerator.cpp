#include "ranlux24numbersgenerator.h"

Ranlux24NumbersGenerator::Ranlux24NumbersGenerator()
{
    _randomNumbersEngine
            = new std::ranlux24_base{static_cast<long unsigned int>(time(nullptr))};
}

Ranlux24NumbersGenerator::~Ranlux24NumbersGenerator()
{
    delete _randomNumbersEngine;
}

double Ranlux24NumbersGenerator::GenerateRandomValue(std::uniform_real_distribution<> &dist)
{
    return dist(*_randomNumbersEngine);
}
