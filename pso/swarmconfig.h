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

    Domain GetVariableStartDomain(int variableNumber);

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
