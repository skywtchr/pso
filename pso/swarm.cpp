#include "swarm.h"

Swarm::Swarm(ILog &logger,
             SwarmConfig &config,
             ObjectiveFunction &objectiveFunction) {
    _logger = &logger;
    _config = &config;
    _objectiveFunction = &objectiveFunction;
}

Swarm::~Swarm() {
    for (auto var : _variablesToDelete) {
        delete var;
    }
}

std::vector<double> Swarm::GetFunctionMinimum()
{
    CreateParticles();
    FindBestSwarmPositionAndResult();
    RunPsoAlgorithm();
    return *_bestSwarmPosition;
}

double Swarm::GetBestSwarmResult()
{
    return _bestSwarmResult;
}

void Swarm::CreateParticles()
{
    for(int i = 0; i<_config->particlesCount; i++) {
        auto particle = GetNewParticle();
        _particles.push_back(particle);
    }
}

void Swarm::FindBestSwarmPositionAndResult()
{
    _bestSwarmPosition = _particles[0].GetPosition();
    _bestSwarmResult = _objectiveFunction->GetResult(*_bestSwarmPosition);
    for (auto particle : _particles) {
        auto bestParticleResult = particle.GetBestResult();
        if (bestParticleResult < _bestSwarmResult) {
            _bestSwarmResult = bestParticleResult;
            _bestSwarmPosition = particle.GetPosition();
        }
    }
}

Particle Swarm::GetNewParticle()
{
    return Particle(*_logger,
                    *_config->particleFactors,
                    *_objectiveFunction,
                    *_config->randomNumbersGenerator,
                    FixStartPosition(),
                    FixStartVelocity(),
                    &_bestSwarmPosition);
}

void Swarm::RunPsoAlgorithm()
{
    for (int i=0; i<_config->iterationCount; i++) {
        for (auto particle : _particles) {
            auto bestParticleResult = particle.GetBestResult();
            if (bestParticleResult < _bestSwarmResult) {
                _bestSwarmResult = bestParticleResult;
                _bestSwarmPosition = particle.GetPosition();
            }
            particle.Move();
        }
    }
}

std::vector<double>* Swarm::FixStartPosition()
{
    std::vector<double>* result = new std::vector<double>();
    _variablesToDelete.push_back(result);

    std::uniform_real_distribution<> dist(-1000, 1000);
    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        auto randomValue
                = _config->randomNumbersGenerator->GenerateRandomValue(dist);
        result->push_back(randomValue);
    }
    return result;
}

std::vector<double>* Swarm::FixStartVelocity()
{
    std::vector<double>* result = new std::vector<double>();
    _variablesToDelete.push_back(result);

    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        result->push_back(0);
    }
    return result;
}
