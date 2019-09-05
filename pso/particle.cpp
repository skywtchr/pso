#include "particle.h"

Particle::Particle(ILog &logger,
                   ParticleFactors &factors,
                   ObjectiveFunction &objectiveFunction,
                   RandomNumbersGenerator *randomNumbersGenerator,
                   std::vector<int>* startPosition,
                   std::vector<int>* startVelocity,
                   std::vector<int>** bestSwarmPosition)
{
    CheckInitialConditions();
    //configs
    _logger = &logger;
    _factors = &factors;
    _objectiveFunction = &objectiveFunction;
    _randomNumbersGenerator = randomNumbersGenerator;
    //position
    _position = startPosition;
    _bestParticlePosition = startPosition;
    //velocity
    _velocity = startVelocity;
    _bestSwarmPosition = bestSwarmPosition;
    //result
    _result = _objectiveFunction->GetResult(*_position);
    _bestParticleResult = _result;
}

Particle::~Particle() { }

void Particle::Move()
{
    UpdateVelocity();
    UpdatePosition();
    UpdateResultAndBestValues();
}

void Particle::CheckInitialConditions()
{
    if (_position->size() > 0 && _position->size() == _velocity->size()) {
        return;
    }
    else {
        auto errorMsg = "Particle position and value size does not match";
        _logger->LogError(errorMsg);
        throw std::invalid_argument(errorMsg);
    }
}

void Particle::UpdateVelocity()
{
    std::uniform_real_distribution<> dist(0, 1);

    double r1 = _randomNumbersGenerator->GenerateRandomValue(dist);
    double r2 = _randomNumbersGenerator->GenerateRandomValue(dist);
    double r3 = _randomNumbersGenerator->GenerateRandomValue(dist);


    for(std::size_t i=0; i<_velocity->size(); i++) {

    (*_velocity)[i] =
            _factors->GetSelfTrust()*r1*(*_velocity)[i]
            + _factors->GetSelfExpirienceTrust()*r2*((*_bestParticlePosition)[i] - (*_position)[i])
            + _factors->GetGroupExpirienceTrust()*r3*((**_bestSwarmPosition)[i] - (*_position)[i]);
    }
}

void Particle::UpdatePosition()
{
    for(std::size_t i=0; i<_position->size(); i++) {
        (*_position)[i] = (*_position)[i] + (*_velocity)[i];
    }
}

void Particle::UpdateResultAndBestValues()
{
    _result = _objectiveFunction->GetResult(*_position);
    if (_result < _bestParticleResult) {
        _bestParticleResult = _result;
        _bestParticlePosition = _position;
    }
}

std::vector<int>* Particle::GetPosition()
{
    return _position;
}

double Particle::GetResult()
{
    return _result;
}

double Particle::GetBestResult()
{
    return _bestParticleResult;
}
