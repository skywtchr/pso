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

    std::vector<int>* GetPosition();
    double GetResult();
    double GetBestResult();
    void Move();

private:
    ILog *_logger;
    ParticleFactors *_factors;
    ObjectiveFunction *_objectiveFunction;
    RandomNumbersGenerator* _randomNumbersGenerator;

    std::vector<int> *_position;
    std::vector<int> *_bestParticlePosition;
    double _result;
    double _bestParticleResult;
    std::vector<int> *_velocity;
    std::vector<int> **_bestSwarmPosition;

    void CheckInitialConditions();
    void UpdateVelocity();
    void UpdatePosition();
    void UpdateResultAndBestValues();
};

#endif // PARTICLE_H
