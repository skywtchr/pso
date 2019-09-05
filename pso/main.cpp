#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "ilog.h"
#include "consolelogger.h"
#include "particle.h"
#include "swarm.h"
#include "swarmconfig.h"
#include "objectivefunction.h"
#include "particlefactors.h"

using namespace std;

double testFunction(std::vector<double>& input)
{
    //expected min -> f(0,0) = 1;
    auto x = input[0];
    auto y = input[1];

    return pow(x,2) + pow(y,2) + 1;
}

double boothFunction(std::vector<double>& input)
{
    //expected min -> f(1,3) = 0;
    auto x = input[0];
    auto y = input[1];

    return pow(x + 2*y - 7, 2) +
            pow (2*x + y - 5, 2);
}

int main()
{
    ILog* logger = new ConsoleLogger();
    ObjectiveFunction objectiveFunction(*logger, &boothFunction, 2);

    //configuration prepare
    SwarmConfig swarmConfig;
    swarmConfig.particleFactors = new ParticleFactors(1,1,10);
    swarmConfig.particlesCount = 100;
    swarmConfig.iterationCount = 1000;
    //----------------x----------------

    //swarm initialize
    Swarm swarm(*logger, swarmConfig, objectiveFunction);
    logger->LogInfo("Swarm initialized.");

    //start alghoritm
    logger->LogInfo("Starting pso algorithm...");
    auto result = swarm.GetFunctionMinimum();
    logger->LogInfo("Execution finished.");

    //write down the results
    logger->LogInfo("Best position is:");
    for(auto pos : result) {
        logger->LogInfo(">> " + to_string(pos));
    }
    logger->LogInfo("For which the value is:");
    logger->LogInfo(to_string(swarm.GetBestSwarmResult()));
    logger->LogInfo("");
}
