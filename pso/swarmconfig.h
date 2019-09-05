#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H

#include <random>
#include <ctime>

#include "randomnumbersgenerator.h"
#include "particlefactors.h"

class SwarmConfig
{
public:
    SwarmConfig();
    ~SwarmConfig();

    int particlesCount;
    int iterationCount;
    RandomNumbersGenerator* randomNumbersGenerator;
    ParticleFactors* particleFactors;

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
