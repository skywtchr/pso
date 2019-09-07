#ifndef SWARM_H
#define SWARM_H

#include <vector>
#include <list>
#include <random>
#include <thread>

#include "ilog.h"
#include "particle.h"
#include "particlefactors.h"
#include "swarmconfig.h"
#include "objectivefunction.h"

class Swarm {

public:
    Swarm(ILog &logger,
          SwarmConfig &config,
          ObjectiveFunction &objectiveFunction);
    ~Swarm();

    std::thread *SearchFunctionMinimumAsync();
    void SearchFunctionMinimum();
    std::vector<double> GetBestSwarmPosition();
    double GetBestSwarmResult();
    int GetProgressPercentageValue();
    int GetProcessedIterationsCount();
    bool IsFinished();

private:
    ILog *_logger;
    SwarmConfig* _config;
    ObjectiveFunction* _objectiveFunction;
    std::vector<Particle> _particles;
    std::vector<double>* _bestSwarmPosition;
    double _bestSwarmResult;

    void CreateParticles();
    void FindBestSwarmPositionAndResult();
    Particle GetNewParticle();
    void RunPsoAlgorithm();
    std::vector<double>* FixStartPosition();
    std::vector<double>* FixStartVelocity();

    int _iterationCounter;
    bool _isFinished;
    std::list<std::vector<double>*> _variablesToDelete;
};

#endif // SWARM_H
