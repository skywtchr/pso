#ifndef SWARM_H
#define SWARM_H

#include <vector>

#include "ilog.h"
#include "particle.h"
#include "swarmconfig.h"

class Swarm {

public:
    Swarm(ILog &logger,
          SwarmConfig &config,
          double (*objectiveFunction)(std::vector<int>&),
          int variablesCount);

    ~Swarm();

    std::vector<int> Start();

private:
    ILog *_logger;
    int _particlesCount;
    int _iterationCount;

    std::vector<Particle> _particles;

    double (*_objectiveFunction)(std::vector<int>&);

    std::vector<int>* _bestSwarmPosition;
    double _bestSwarmResult;
    int _variablesCount;

    //methods
    void CreateParticles();
    Particle GetParticle();
    std::vector<int>* FixStartPosition();
    std::vector<int>* FixStartVelocity();

};

#endif // SWARM_H
