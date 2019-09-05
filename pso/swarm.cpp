#include "swarm.h"

Swarm::Swarm(ILog &logger,
             SwarmConfig &config,
             ObjectiveFunction &objectiveFunction) {
    _logger = &logger;
    _config = &config;
    _objectiveFunction = &objectiveFunction;
}

Swarm::~Swarm() {
}

std::vector<int> Swarm::Start() {

    CreateParticles();
    _bestSwarmPosition = _particles[0].GetPosition();
    _bestSwarmResult = _objectiveFunction->GetResult(*_bestSwarmPosition);

    for (int i=0; i<_config->iterationCount; i++) {

        for (auto particle : _particles) {
            auto result = particle.UpdateCurrentPositionResult();
            if (result < _bestSwarmResult) {
                _bestSwarmResult = result;
                _bestSwarmPosition = particle.GetPosition();
            }
            particle.Move();
        }
    }

    return *_bestSwarmPosition;
}

void Swarm::CreateParticles() {
    for(int i = 0; i<_config->particlesCount; i++) {
        auto particle = GetParticle();
        _particles.push_back(particle);
    }
}

Particle Swarm::GetParticle() {

    ParticleFactors particleFactors(0, 0, 10);

    return Particle(*_logger,
                    particleFactors,
                    *_objectiveFunction,
                    &_config->randomNumbersGenerator,
                    FixStartPosition(),
                    FixStartVelocity(),
                    &_bestSwarmPosition);
}

std::vector<int>* Swarm::FixStartPosition()
{
    std::vector<int>* result = new std::vector<int>();

    std::uniform_real_distribution<> dist(-1000, 1000);

    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        auto randomValue
                = _config->randomNumbersGenerator.GenerateRandomValue(dist);
        result->push_back(randomValue);
    }
    return result;
}

std::vector<int>* Swarm::FixStartVelocity()
{
    std::vector<int>* result = new std::vector<int>();
    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        result->push_back(0);
    }
    return result;
}
