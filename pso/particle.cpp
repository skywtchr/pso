#include "particle.h"

Particle::Particle(ILog &logger,
                   ParticleFactors &factors,
                   ObjectiveFunction &objectiveFunction,
                   RandomNumbersGenerator *randomNumbersGenerator,
                   std::vector<int>* startPosition,
                   std::vector<int>* startVelocity,
                   std::vector<int>** bestSwarmPosition)
{
    _logger = &logger;
    _objectiveFunction = &objectiveFunction;
    _randomNumbersGenerator = randomNumbersGenerator;

    _position = startPosition;
    _bestParticlePosition = startPosition;
    _velocity = startVelocity;
    _bestSwarmPosition = bestSwarmPosition;
    _factors = &factors;

    CheckStartConditions();
    _bestParticleResult = _objectiveFunction->GetResult(*_position);
}

Particle::~Particle() {
}

double Particle::UpdateCurrentPositionResult() {
    auto result = _objectiveFunction->GetResult(*_position);

    if (result < _bestParticleResult) {
        _bestParticleResult = result;
        _bestParticlePosition = _position;
    }
    return result;
}

void Particle::Move() {
    std::uniform_real_distribution<> dist(0, 1);

    double r1 = _randomNumbersGenerator->GenerateRandomValue(dist);
    double r2 = _randomNumbersGenerator->GenerateRandomValue(dist);
    double r3 = _randomNumbersGenerator->GenerateRandomValue(dist);

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

    for(int i=0; i<_velocity->size(); i++) {
        (*_velocity)[i] =
            _factors->GetSelfTrust()*r1*(*_velocity)[i]
            + _factors->GetSelfExpirienceTrust()*r2*((*_bestParticlePosition)[i] - (*_position)[i])
            + _factors->GetGroupExpirienceTrust()*r3*((**_bestSwarmPosition)[i] - (*_position)[i]);
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
