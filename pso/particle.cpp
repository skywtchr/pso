#include "particle.h"

Particle::Particle(ILog &logger,
        double c1,
        double c2,
        double c3,
        std::vector<int> *startPosition,
        std::vector<int> *startVelocity,
        std::vector<int>** bestSwarmPosition,
        double (*objectiveFunction)(std::vector<int>&))
{
    _logger = &logger;
    _position = startPosition;
    _bestParticlePosition = startPosition;
    _velocity = startVelocity;
    _bestSwarmPosition = bestSwarmPosition;

    _objectiveFunction = objectiveFunction;

    _c1 = c1;
    _c2 = c2;
    _c3 = c3;

    CheckStartConditions();

    _bestParticleResult = (*_objectiveFunction)(*_position);
}

Particle::~Particle() {
}

double Particle::UpdateCurrentPositionResult() {
    auto result = (*_objectiveFunction)(*_position);

    if (result < _bestParticleResult) {
        _bestParticleResult = result;
        _bestParticlePosition = _position;
    }
    return result;
}

void Particle::Move(double r1, double r2, double r3) {
    UpdateVelocity(r1,r2,r3);
    UpdatePosition();
}

void Particle::CheckStartConditions() {
    if (_position->size() > 0 && _position->size() == _velocity->size()) {
        return;
    }
    else {
        auto errorMsg = "Particle position and value size does not match";
        _logger->LogError(errorMsg);
        throw std::invalid_argument(errorMsg);
    }
}

void Particle::UpdateVelocity(double r1, double r2, double r3) {

    // std::random_device rd;
    // std::ranlux24_base e2(rd());
    // std::uniform_real_distribution<> dist(0, 1);

    for(int i=0; i<_velocity->size(); i++) {
        (*_velocity)[i] =
            _c1*r1*(*_velocity)[i]
            + _c2*r2*((*_bestParticlePosition)[i] - (*_position)[i])
            + _c3*r3*((**_bestSwarmPosition)[i] - (*_position)[i]);
    }
}

void Particle::UpdatePosition() {

    for(int i=0; i<_position->size(); i++) {
        (*_position)[i] = (*_position)[i] + (*_velocity)[i];
    }
}

std::vector<int>* Particle::GetPosition() {
    return _position;
}
