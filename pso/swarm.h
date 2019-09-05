#ifndef SWARM_H
#define SWARM_H

#include <vector>
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

    std::vector<int> Start();

private:
    ILog *_logger;
    SwarmConfig* _config;
    ObjectiveFunction* _objectiveFunction;
    std::vector<Particle> _particles;
    std::vector<int>* _bestSwarmPosition;
    double _bestSwarmResult;

    void CreateParticles();
    Particle GetParticle();
    std::vector<int>* FixStartPosition();
    std::vector<int>* FixStartVelocity();
};

#endif // SWARM_H
