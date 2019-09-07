#include "swarmconfig.h"

SwarmConfig::SwarmConfig(ILog &logger)
{
    _logger = &logger;
    particlesCount = 30;
    iterationCount = 500;

    randomNumbersGenerator = new Ranlux24NumbersGenerator();
    _randomNumbersGeneratorToDelete = randomNumbersGenerator;

    particleFactors = new ParticleFactors(0, 0, 5);
    _particleFactorsToDelete = particleFactors;

    variablesStartDomains = nullptr;
    _variablesStartDomainsToDelete = nullptr;

    velocityLimit = nullptr;
    _velocityLimitToDelete = nullptr;
}

SwarmConfig::~SwarmConfig()
{
    delete _randomNumbersGeneratorToDelete;
    delete _particleFactorsToDelete;
    delete _variablesStartDomainsToDelete;
    delete _velocityLimitToDelete;
}

Domain SwarmConfig::GetVariableStartDomain(int variableNumber)
{
    if (variablesStartDomains == nullptr) {
        return Domain(-1000, 1000);
    }
    if (variableNumber < 0 ||
            variableNumber > (static_cast<int>(variablesStartDomains->size()))) {
        auto errorMsg = "Out of bounds variableNumber: "
                + std::to_string(variableNumber);
        _logger->LogError(errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    return (*variablesStartDomains)[static_cast<size_t>(variableNumber)];
}
