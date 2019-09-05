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

double sphereFunction(std::vector<double>& input)
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

void testPso(ILog &logger,
             double (*function)(std::vector<double>&),
             int parametersCount,
             SwarmConfig swarmConfig,
             string description) {

    ObjectiveFunction objectiveFunction(logger, function, parametersCount);
    Swarm swarm(logger, swarmConfig, objectiveFunction);
    auto result = swarm.GetFunctionMinimum();

    //write down the results
    cout << description << endl;
    cout << "Obtained result:" << endl;
    cout << "f( ";
    for(auto pos : result) {
        cout << to_string(pos) << ", ";
    }
    cout << ") = " << to_string(swarm.GetBestSwarmResult()) << endl;
    cout << "-----------------x-----------------" << endl;
}

int main()
{
    ILog* logger = new ConsoleLogger();

    cout << "SPHERE FUNCTION" << endl;
    SwarmConfig sphereConfig(*logger);
    sphereConfig.particleFactors = new ParticleFactors(0,3,4);
    sphereConfig.particlesCount = 50;
    sphereConfig.iterationCount = 1000;
    testPso(*logger, sphereFunction, 2, sphereConfig, "expected min -> f(0,0) = 1");

    cout << "BOOTH FUNCTION" << endl;
    SwarmConfig boothConfig(*logger);
    boothConfig.particleFactors = new ParticleFactors(0,3,4);
    boothConfig.particlesCount = 50;
    boothConfig.iterationCount = 1000;
    testPso(*logger, boothFunction, 2, boothConfig, "expected min -> f(1,3) = 0");

    delete logger;
}
