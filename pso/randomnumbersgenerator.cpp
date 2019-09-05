#include "randomnumbersgenerator.h"

RandomNumbersGenerator::RandomNumbersGenerator()
{
    _randomNumbersEngine
            = new std::ranlux24_base{static_cast<long unsigned int>(time(nullptr))};
}

double RandomNumbersGenerator::GenerateRandomValue(std::uniform_real_distribution<> &dist)
{
    return dist(*_randomNumbersEngine);
}
