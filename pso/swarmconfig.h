#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H

#include <random>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <string>

#include "irandomnumbersgenerator.h"
#include "ranlux24numbersgenerator.h"
#include "particlefactors.h"
#include "domain.h"
#include "ilog.h"
#include "velocitylimit.h"

class SwarmConfig
{
public:
    SwarmConfig(ILog &logger);
    ~SwarmConfig();

    ILog *_logger;
    int particlesCount;
    int iterationCount;
    IRandomNumbersGenerator* randomNumbersGenerator;
    ParticleFactors* particleFactors;
    std::vector<Domain>* variablesStartDomains;
    VelocityLimit* velocityLimit;

    Domain GetVariableStartDomain(int variableNumber);

private:
    IRandomNumbersGenerator* _randomNumbersGeneratorToDelete;
    ParticleFactors* _particleFactorsToDelete;
    std::vector<Domain>* _variablesStartDomainsToDelete;
    VelocityLimit* _velocityLimitToDelete;
};

#endif // SWARMCONFIG_H
