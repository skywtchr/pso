#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <future>
#include <thread>

#include "ilog.h"
#include "consolelogger.h"
#include "particle.h"
#include "swarm.h"
#include "swarmconfig.h"
#include "objectivefunction.h"
#include "particlefactors.h"

using namespace std;

double sphereFunction(std::vector<double>& input)
{
    //expected min -> f(0,0) = 1;
    auto x = input[0];
    auto y = input[1];

    return pow(x,2) + pow(y,2) + 1;
}

double threeArgsFunction(std::vector<double>& input)
{
    //expected min -> f(0,0,0) = 1;
    auto x = input[0];
    auto y = input[1];
    auto z = input[2];

    return pow(x-1,2) + pow(y-1,2) + pow(z-2,2) + 1;
}

double boothFunction(std::vector<double>& input)
{
    //expected min -> f(1,3) = 0;
    auto x = input[0];
    auto y = input[1];

    return pow(x + 2*y - 7, 2) +
            pow (2*x + y - 5, 2);
}

double bukinFunction(std::vector<double>& input)
{
    //expected min -> f(-10,1) = 0;
    auto x = input[0];
    auto y = input[1];

    return 100*pow(abs(y - 0.01*x*x), 0.5) +
            0.01*abs(x+10);
}

double matyasFunction(std::vector<double>& input)
{
    //expected min -> f(0.0) = 0;
    auto x = input[0];
    auto y = input[1];

    return 0.26*(x*x + y*y) - 0.48*x*y;
}

double leviFunction(std::vector<double>& input)
{
    //expected min -> f(1,1) = 0;
    auto x = input[0];
    auto y = input[1];

    return pow(sin(3*M_PI*x), 2) +
            pow(x-1, 2)*(1+pow(sin(3*M_PI*y), 2)) +
            pow(y-1, 2)*(1+pow(sin(2*M_PI*y), 2));
}

double easonFunction(std::vector<double>& input)
{
    //expected min -> f(PI,PI) = -1;
    auto x = input[0];
    auto y = input[1];

    return (-1)*cos(x)*cos(y)*exp((-1)*(pow(x-M_PI,2) + pow(y-M_PI,2)));
}

double mcCornickFunction(std::vector<double>& input)
{
    //expected min -> f(-0.54719,-1.54719) = -1.9133;
    auto x = input[0];
    auto y = input[1];

    return sin(x+y) + pow(x-y,2) - 1.5*x + 2.5*y + 1;
}

void WriteDownTheResults(std::vector<double>& bestPosition,
                         double bestResult,
                         string description) {
    cout << description << endl;
    cout << "Obtained result:" << endl;
    cout << "f( ";
    for(auto pos : bestPosition) {
        cout << to_string(pos) << ", ";
    }
    cout << ") = " << to_string(bestResult) << endl;
    cout << "-----------------x-----------------" << endl;
}

void WriteProgress(
        int iterationProgress,
        int allIterationCount,
        int percentageProgress) {
    cout << "\r"
         << "Progress: "
         << percentageProgress << " % "
         << "of " << allIterationCount << " iterations, "
         << "current: " << iterationProgress;
}

void TestPso(ILog &logger,
             double (*function)(std::vector<double>&),
             int parametersCount,
             SwarmConfig swarmConfig,
             string description) {

    //run the algorithm
    ObjectiveFunction objectiveFunction(logger, function, parametersCount);
    Swarm swarm(logger, swarmConfig, objectiveFunction);
    swarm.SearchFunctionMinimumAsync();

    //track the progress
    while(!swarm.IsFinished()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto percentageProgress = swarm.GetPercentageProgress();
        auto iterationProgress = swarm.GetIterationProgress();
        auto allIterationCount = swarm.GetIterationCount();
        WriteProgress(iterationProgress, allIterationCount, percentageProgress);
    }
    auto percentageProgress = swarm.GetPercentageProgress();
    auto iterationProgress = swarm.GetIterationProgress();
    auto allIterationCount = swarm.GetIterationCount();
    WriteProgress(iterationProgress, allIterationCount, percentageProgress);
    cout << endl;

    //write down the results
    auto bestPosition = swarm.GetBestSwarmPosition();
    auto bestResult = swarm.GetBestSwarmResult();
    WriteDownTheResults(bestPosition, bestResult, description);
}

int main()
{
    ILog* logger = new ConsoleLogger(ConsoleLoggerMode::WARN);

    cout << "THREE ARGS FUNCTION" << endl;
    SwarmConfig threeConfig(*logger);
    auto threeArgsParticleFactors = new ParticleFactors(0,3,4);
    threeConfig.particleFactors = threeArgsParticleFactors;
    threeConfig.particlesCount = 50;
    threeConfig.iterationCount = 100000;
    TestPso(*logger, threeArgsFunction, 3, threeConfig, "Expected min -> f(1,1,2) = 1;");
    delete threeArgsParticleFactors;

    cout << "SPHERE FUNCTION" << endl;
    SwarmConfig sphereConfig(*logger);
    auto sphereParticleFactors = new ParticleFactors(0,3,4);
    sphereConfig.particleFactors = sphereParticleFactors;
    sphereConfig.particlesCount = 50;
    sphereConfig.iterationCount = 10000;
    TestPso(*logger, sphereFunction, 2, sphereConfig, "Expected min -> f(0,0) = 1");
    delete sphereParticleFactors;

    cout << "BOOTH FUNCTION" << endl;
    SwarmConfig boothConfig(*logger);
    auto boothParticleFactors = new ParticleFactors(0,3,4);
    boothConfig.particleFactors = boothParticleFactors;
    boothConfig.particlesCount = 50;
    boothConfig.iterationCount = 1000;
    TestPso(*logger, boothFunction, 2, boothConfig, "Expected min -> f(1,3) = 0");
    delete boothParticleFactors;

    cout << "EASON FUNCTION" << endl;
    SwarmConfig easonConfig(*logger);
    auto easonParticleFactors = new ParticleFactors(0,3,2);
    easonConfig.particleFactors = easonParticleFactors;
    easonConfig.particlesCount = 50;
    easonConfig.iterationCount = 1000;
    std::vector<Domain> easonDomains;
    easonDomains.push_back(Domain(-100, 100));
    easonDomains.push_back(Domain(-100, 100));
    easonConfig.variablesStartDomains = &easonDomains;
    easonConfig.velocityLimit = new VelocityLimit(4, VelocityLimitMode::LenghtLimit);
    TestPso(*logger, easonFunction, 2, easonConfig, "Expected min -> f(PI,PI) = -1");
    delete easonParticleFactors;

    cout << "LEVI FUNCTION" << endl;
    SwarmConfig leviConfig(*logger);
    auto leviParticleFactors = new ParticleFactors(0,3,4);
    leviConfig.particleFactors = leviParticleFactors;
    leviConfig.particlesCount = 50;
    leviConfig.iterationCount = 1000;
    TestPso(*logger, leviFunction, 2, leviConfig, "Expected min -> f(1,1) = 0");
    delete leviParticleFactors;

    cout << "MC CORNICK FUNCTION" << endl;
    SwarmConfig mcCornickConfig(*logger);
    auto mcCornickParticleFactors = new ParticleFactors(0,3,3);
    mcCornickConfig.particleFactors = mcCornickParticleFactors;
    mcCornickConfig.particlesCount = 50;
    mcCornickConfig.iterationCount = 1000;
    std::vector<Domain> mcCornickDomains;
    mcCornickDomains.push_back(Domain(-1.5, 4));
    mcCornickDomains.push_back(Domain(-3, 4));
    mcCornickConfig.variablesStartDomains = &mcCornickDomains;
    mcCornickConfig.velocityLimit = new VelocityLimit(2, VelocityLimitMode::StandardLimit);
    TestPso(*logger, mcCornickFunction, 2, mcCornickConfig, "Expected min -> f(-0.54719,-1.54719) = -1.9133");
    delete mcCornickParticleFactors;

    delete logger;
}
