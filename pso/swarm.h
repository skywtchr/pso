#ifndef SWARM_H
#define SWARM_H

#include <vector>
#include <list>
#include <random>
#include <future>

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
    Swarm(ILog &logger,
          ObjectiveFunction &objectiveFunction);
    ~Swarm();

    void SearchFunctionMinimumAsync();
    void SearchFunctionMinimumSync();
    std::vector<double> GetBestSwarmPosition();
    double GetBestSwarmResult();
    int GetPercentageProgress();
    int GetIterationProgress();
    int GetIterationCount();
    bool IsFinished();

private:
    ILog *_logger;
    SwarmConfig* _config;
    ObjectiveFunction* _objectiveFunction;
    std::vector<Particle> _particles;
    std::vector<double>* _bestSwarmPosition;
    double _bestSwarmResult;

    void SearchFunctionMinimum();
    void CreateParticles();
    void FindBestSwarmPositionAndResult();
    Particle GetNewParticle();
    void RunPsoAlgorithm();
    std::vector<double>* FixStartPosition();
    std::vector<double>* FixStartVelocity();

    int _iterationCounter;
    bool _isFinished;
    std::future<void> _searchingFuture;

    //cleanup
    SwarmConfig* _configToDelete;
    std::list<std::vector<double>*> _vectorsToDelete;
};

#endif // SWARM_H
