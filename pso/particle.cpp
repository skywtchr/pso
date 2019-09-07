#include "particle.h"

Particle::Particle(ILog &logger,
                   ParticleFactors &factors, VelocityLimit *velocityLimit,
                   ObjectiveFunction &objectiveFunction,
                   IRandomNumbersGenerator &randomNumbersGenerator,
                   std::vector<double>* startPosition,
                   std::vector<double>* startVelocity,
                   std::vector<double>** bestSwarmPosition)
{
    //configs
    _logger = &logger;
    _factors = &factors;
    _velocityLimit = velocityLimit;
    _objectiveFunction = &objectiveFunction;
    _randomNumbersGenerator = &randomNumbersGenerator;
    //position
    _position = startPosition;
    _bestParticlePosition = startPosition;
    //velocity
    _velocity = startVelocity;
    _bestSwarmPosition = bestSwarmPosition;
    //validation after assigning
    ValidateInitialValues();
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

void Particle::ValidateInitialValues()
{
    if (static_cast<int>(_position->size()) == _objectiveFunction->GetVariablesCount()
            && _position->size() == _velocity->size()) {
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
    for(std::size_t i=0; i<_velocity->size(); i++) {

        auto selfVelocityPart =
                _factors->GetSelfTrust() *
                _randomNumbersGenerator->GenerateRandomValue(dist) *
                (*_velocity)[i];
        auto selfExpiriencePart =
                _factors->GetSelfExpirienceTrust() *
                _randomNumbersGenerator->GenerateRandomValue(dist) *
                ((*_bestParticlePosition)[i] - (*_position)[i]);
        auto groupExpiriencePart =
                _factors->GetGroupExpirienceTrust() *
                _randomNumbersGenerator->GenerateRandomValue(dist) *
                ((**_bestSwarmPosition)[i] - (*_position)[i]);

        (*_velocity)[i] = selfVelocityPart + selfExpiriencePart + groupExpiriencePart;
    }
    FixVelocityToBeWithinLimit();
}

void Particle::FixVelocityToBeWithinLimit()
{
    if (_velocityLimit == nullptr) {
        return;
    }
    if (_velocityLimit->GetMode() == VelocityLimitMode::StandardLimit) {
        for (size_t i=0; i<_velocity->size(); i++) {
            auto current = _velocity->at(i);
            auto max = _velocityLimit->GetMaxValue();
            auto min = max*(-1);
            if (current > max) {
                _velocity->at(i) = max;
            }
            if (current < min) {
                _velocity->at(i) = min;
            }
        }
        return;
    }
    auto velocityLenght = GetVelocityLenght();
    if (_velocityLimit->GetMode() == VelocityLimitMode::LenghtLimit) {
        for (size_t i=0; i<_velocity->size(); i++) {
            auto current = _velocity->at(i);
            auto max = _velocityLimit->GetMaxValue();
            auto min = max*(-1);
            if (current > max) {
                _velocity->at(i) = max * current / velocityLenght;
            }
            if (current < min) {
                _velocity->at(i) = max * current / velocityLenght;
            }
        }
        return;
    }
}

double Particle::GetVelocityLenght()
{
    double result = 0;
    for (auto v : *_velocity) {
        result += pow(v, 2);
    }
    return pow(result, 0.5);
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

std::vector<double>* Particle::GetPosition()
{
    return _position;
}

std::vector<double> *Particle::GetBestPosition()
{
    return _bestParticlePosition;
}

double Particle::GetResult()
{
    return _result;
}

double Particle::GetBestResult()
{
    return _bestParticleResult;
}
