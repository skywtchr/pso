#include "swarmconfig.h"

SwarmConfig::SwarmConfig(ILog &logger)
{
    _logger = &logger;
    SetDefaultValues();
}

SwarmConfig::~SwarmConfig()
{
    delete randomNumbersGenerator;
    delete particleFactors;
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

void SwarmConfig::SetDefaultValues()
{
    particlesCount = 30;
    iterationCount = 500;
    randomNumbersGenerator = new Ranlux24NumbersGenerator();
    particleFactors = new ParticleFactors(0, 0, 5);
    variablesStartDomains = nullptr;
}
