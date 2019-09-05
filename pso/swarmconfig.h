#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H

#include <random>
#include <ctime>

#include "irandomnumbersgenerator.h"
#include "ranlux24numbersgenerator.h"
#include "particlefactors.h"

class SwarmConfig
{
public:
    SwarmConfig();
    ~SwarmConfig();

    int particlesCount;
    int iterationCount;
    IRandomNumbersGenerator* randomNumbersGenerator;
    ParticleFactors* particleFactors;

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
