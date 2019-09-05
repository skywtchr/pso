#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H

#include <random>
#include <ctime>

#include "randomnumbersgenerator.h"

class SwarmConfig
{
public:
    SwarmConfig();

    int particlesCount;
    int iterationCount;
    RandomNumbersGenerator randomNumbersGenerator;

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
