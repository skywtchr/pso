#include "swarm.h"

Swarm::Swarm(ILog &logger,
             SwarmConfig &config,
             ObjectiveFunction &objectiveFunction) {
    _logger = &logger;
    _config = &config;
    _objectiveFunction = &objectiveFunction;
    _isFinished = false;
    _iterationCounter = 0;
    _configToDelete = nullptr;
}

Swarm::Swarm(ILog &logger, ObjectiveFunction &objectiveFunction)
{
    _logger = &logger;
    _config = new SwarmConfig(logger);
    _configToDelete = _config;
    _objectiveFunction = &objectiveFunction;
    _isFinished = false;
    _iterationCounter = 0;
}

Swarm::~Swarm() {
    for (auto var : _vectorsToDelete) {
        delete var;
    }
    delete _configToDelete;
}

void Swarm::SearchFunctionMinimumAsync()
{
    auto asynOperation = [] (Swarm* s) {
        s->SearchFunctionMinimum();
    };
    _searchingFuture = std::async(std::launch::async, asynOperation, this);
}

void Swarm::SearchFunctionMinimumSync()
{
    SearchFunctionMinimum();
}

std::vector<double> Swarm::GetBestSwarmPosition()
{
    return *_bestSwarmPosition;
}

void Swarm::SearchFunctionMinimum()
{
    CreateParticles();
    FindBestSwarmPositionAndResult();
    RunPsoAlgorithm();
    _isFinished = true;
}

double Swarm::GetBestSwarmResult()
{
    return _bestSwarmResult;
}

int Swarm::GetPercentageProgress()
{
    return 100 * _iterationCounter / _config->iterationCount;
}

int Swarm::GetIterationProgress()
{
    return _iterationCounter;
}

int Swarm::GetIterationCount()
{
    return _config->iterationCount;
}

std::vector<Particle> *Swarm::GetParticles()
{
    return &_particles;
}

bool Swarm::IsFinished()
{
    return _isFinished;
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
    _logger->LogInfo("PSO algorithm started...");
    for (int i=0; i<_config->iterationCount; i++) {
        _iterationCounter = i+1;
        for (auto particle : _particles) {
            particle.Move();
            auto bestParticleResult = particle.GetBestResult();
            if (bestParticleResult < _bestSwarmResult) {
                _bestSwarmResult = bestParticleResult;
                _bestSwarmPosition = particle.GetPosition();
            }
        }
    }
    _logger->LogInfo("PSO algorithm finished successfully.");
}

std::vector<double>* Swarm::FixStartPosition()
{
    std::vector<double>* result = new std::vector<double>();
    _vectorsToDelete.push_back(result);

    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        auto startDomain = _config->GetVariableStartDomain(i);

        std::uniform_real_distribution<> dist(startDomain.GetLowerLimit(), startDomain.GetUpperLimit());
        auto randomValue
                = _config->randomNumbersGenerator->GenerateRandomValue(dist);
        result->push_back(randomValue);
    }
    return result;
}

std::vector<double>* Swarm::FixStartVelocity()
{
    std::vector<double>* result = new std::vector<double>();
    _vectorsToDelete.push_back(result);

    for (int i=0; i<_objectiveFunction->GetVariablesCount(); i++) {
        result->push_back(0);
    }
    return result;
}
