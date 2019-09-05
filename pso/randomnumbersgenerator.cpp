#include "randomnumbersgenerator.h"

RandomNumbersGenerator::RandomNumbersGenerator()
{
    _randomNumbersEngine
            = new std::ranlux24_base{static_cast<long unsigned int>(time(nullptr))};
}

RandomNumbersGenerator::~RandomNumbersGenerator()
{
    delete _randomNumbersEngine;
}

double RandomNumbersGenerator::GenerateRandomValue(std::uniform_real_distribution<> &dist)
{
    return dist(*_randomNumbersEngine);
}
