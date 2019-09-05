#include "swarmconfig.h"

SwarmConfig::SwarmConfig()
{
    SetDefaultValues();
}

SwarmConfig::~SwarmConfig()
{
    delete randomNumbersGenerator;
    delete particleFactors;
}

void SwarmConfig::SetDefaultValues()
{
    particlesCount = 30;
    iterationCount = 500;
    randomNumbersGenerator = new RandomNumbersGenerator();
    particleFactors = new ParticleFactors(0, 0, 5);
}
