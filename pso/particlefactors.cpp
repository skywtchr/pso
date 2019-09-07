#include "particlefactors.h"

ParticleFactors::ParticleFactors(double inertion,
                                 double selfExpirienceTrust,
                                 double groupExpirienceTrust)
{
    _inertion = inertion;
    _selfExpirienceTrust = selfExpirienceTrust;
    _groupExpirienceTrust = groupExpirienceTrust;
}

double ParticleFactors::GetSelfTrust() const
{
    return _inertion;
}

double ParticleFactors::GetSelfExpirienceTrust() const
{
    return _selfExpirienceTrust;
}

double ParticleFactors::GetGroupExpirienceTrust() const
{
    return _groupExpirienceTrust;
}
