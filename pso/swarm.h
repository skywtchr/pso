#ifndef SWARM_H
#define SWARM_H

#include <vector>
#include <list>
#include <random>

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

    std::vector<double> GetFunctionMinimum();

private:
    ILog *_logger;
    SwarmConfig* _config;
    ObjectiveFunction* _objectiveFunction;
    std::vector<Particle> _particles;
    std::vector<double>* _bestSwarmPosition;
    double _bestSwarmResult;

    void CreateParticles();
    Particle GetNewParticle();
    void RunPsoAlgorithm();
    std::vector<double> *FixStartPosition();
    std::vector<double>* FixStartVelocity();

    std::list<std::vector<double>*> _variablesToDelete;
};

#endif // SWARM_H
