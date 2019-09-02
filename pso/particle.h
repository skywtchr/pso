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

class Particle {

public:
    Particle(ILog &logger,
        double c1,
        double c2,
        double c3,
        std::vector<int>* startPosition,
        std::vector<int>* startVelocity,
        std::vector<int>** bestSwarmPosition,
        double (*objectiveFunction)(std::vector<int>&));
    ~Particle();

    double UpdateCurrentPositionResult();
    void Move(double r1, double r2, double r3);
    std::vector<int>* GetPosition();

private:
    // fields
    ILog *_logger;

    double (*_objectiveFunction)(std::vector<int>&);

    std::vector<int> *_position;
    std::vector<int> *_velocity;

    std::vector<int> *_bestParticlePosition;
    std::vector<int>** _bestSwarmPosition;

    double _bestParticleResult;

    // std::set<Particle*> _neighbours;
    // std::vector<int> _bestNeighboursPosition;

    double _c1,_c2,_c3;

    // methods
    void CheckStartConditions();
    void UpdateVelocity(double r1, double r2, double r3);
    void UpdatePosition();
};

#endif // PARTICLE_H
