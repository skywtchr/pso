#include "swarm.h"

Swarm::Swarm(ILog &logger, int particlesCount, int iterationCount, double (*objectiveFunction)(std::vector<int>&),
    int variablesCount) {
    _logger = &logger;
    _particlesCount = particlesCount;
    _iterationCount = iterationCount;

    _objectiveFunction = objectiveFunction;
    _variablesCount = variablesCount;
}

Swarm::~Swarm() {

}

std::vector<int> Swarm::Start() {

    CreateParticles();
    _bestSwarmPosition = _particles[0].GetPosition();
    _bestSwarmResult = (*_objectiveFunction)(*_bestSwarmPosition);

    std::random_device rd;
    std::ranlux24_base gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    for (int i=0; i<_iterationCount; i++) {

        for (auto particle : _particles) {
            auto result = particle.UpdateCurrentPositionResult();
            if (result < _bestSwarmResult) {
                _bestSwarmResult = result;
                _bestSwarmPosition = particle.GetPosition();
            }

            double r1 = dist(gen);
            double r2 = dist(gen);
            double r3 = dist(gen);

            particle.Move(r1,r2,r3);
        }
    }

    return *_bestSwarmPosition;
}

void Swarm::CreateParticles() {
    for(int i = 0; i<_particlesCount; i++) {
        auto particle = GetParticle();
        _particles.push_back(particle);
    }
}

Particle Swarm::GetParticle() {

    double c1 = 2;
    double c2 = 2;
    double c3 = 4;

    return Particle(*_logger,
                c1,
                c2,
                c3,
                FixStartPosition(),
                FixStartVelocity(),
                &_bestSwarmPosition,
                _objectiveFunction);
}

std::vector<int>* Swarm::FixStartPosition(){

    std::vector<int>* result = new std::vector<int>();

    std::random_device rd;
    std::mt19937  gen(rd());
    std::uniform_real_distribution<> dist(-1000, 1000);

    for (int i=0; i<_variablesCount; i++) {
        result->push_back(dist(gen));
    }

    return result;
}

std::vector<int>* Swarm::FixStartVelocity(){

    std::vector<int>* result = new std::vector<int>();

    // std::random_device rd;
    // std::ranlux24_base gen(rd());
    // std::uniform_real_distribution<> dist(-1000, 1000);

    for (int i=0; i<_variablesCount; i++) {
        result->push_back(0);
    }

    return result;
}
