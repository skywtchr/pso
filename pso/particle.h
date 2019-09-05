#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <set>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <map>
#include <random>

#include "ilog.h"
#include "objectivefunction.h"
#include "particlefactors.h"
#include "randomnumbersgenerator.h"

class Particle {

public:
    Particle(ILog &logger,
        ParticleFactors &factors,
        ObjectiveFunction &objectiveFunction,
        RandomNumbersGenerator* randomNumbersGenerator,
        std::vector<int>* startPosition,
        std::vector<int>* startVelocity,
        std::vector<int>** bestSwarmPosition);
    ~Particle();

    double UpdateCurrentPositionResult();
    void Move();
    std::vector<int>* GetPosition();

private:
    ILog *_logger;
    ObjectiveFunction *_objectiveFunction;
    RandomNumbersGenerator* _randomNumbersGenerator;

    std::vector<int> *_position;
    std::vector<int> *_velocity;

    std::vector<int> *_bestParticlePosition;
    std::vector<int> **_bestSwarmPosition;

    double _bestParticleResult;

    ParticleFactors *_factors;

    void CheckStartConditions();
    void UpdateVelocity(double r1, double r2, double r3);
    void UpdatePosition();
};

#endif // PARTICLE_H
