#include <iostream>
#include <vector>
#include <string>

#include "ilog.h"
#include "consolelogger.h"
#include "particle.h"
#include "swarm.h"
#include "swarmconfig.h"
#include "objectivefunction.h"
#include "particlefactors.h"

using namespace std;

double testFunc(std::vector<double>& input) {

    return std::pow(input[0],2) + std::pow(input[1],2) + 1;
}

int main() {

    ILog* logger = new ConsoleLogger();

    SwarmConfig swarmConfig;
    swarmConfig.particleFactors = new ParticleFactors(0,0,5);

    ObjectiveFunction objectiveFunction(*logger, &testFunc, 2);

    Swarm swarm(*logger, swarmConfig, objectiveFunction);
    logger->LogInfo("Swarm initialized.");

    logger->LogInfo("Starting pso alghoritm...");
    auto result = swarm.GetFunctionMinimum();
    logger->LogInfo("Execution finished.");

    logger->LogInfo("Best position is:");
    for(auto pos : result) {
        logger->LogInfo(to_string(pos));
    }
}
