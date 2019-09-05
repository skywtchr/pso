#include "particlefactors.h"

ParticleFactors::ParticleFactors(double selfTrust,
                                 double selfExpirienceTrust,
                                 double groupExpirienceTrust)
{
    _selfTrust = selfTrust;
    _selfExpirienceTrust = selfExpirienceTrust;
    _groupExpirienceTrust = groupExpirienceTrust;
}

double ParticleFactors::GetSelfTrust() const
{
    return _selfTrust;
}

double ParticleFactors::GetSelfExpirienceTrust() const
{
    return _selfExpirienceTrust;
}

double ParticleFactors::GetGroupExpirienceTrust() const
{
    return _groupExpirienceTrust;
}
