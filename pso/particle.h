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
        RandomNumbersGenerator &randomNumbersGenerator,
        std::vector<double>* startPosition,
        std::vector<double>* startVelocity,
        std::vector<double>** bestSwarmPosition);
    ~Particle();

    std::vector<double>* GetPosition();
    std::vector<double>* GetBestPosition();
    double GetResult();
    double GetBestResult();
    void Move();

private:
    ILog *_logger;
    ParticleFactors *_factors;
    ObjectiveFunction *_objectiveFunction;
    RandomNumbersGenerator *_randomNumbersGenerator;

    std::vector<double> *_position;
    std::vector<double> *_bestParticlePosition;
    double _result;
    double _bestParticleResult;
    std::vector<double> *_velocity;
    std::vector<double> **_bestSwarmPosition;

    void CheckInitialConditions();
    void UpdateVelocity();
    void UpdatePosition();
    void UpdateResultAndBestValues();
};

#endif // PARTICLE_H
