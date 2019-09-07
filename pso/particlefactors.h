#ifndef PARTICLEFACTORS_H
#define PARTICLEFACTORS_H


class ParticleFactors
{
public:
    ParticleFactors(double inertion,
                    double selfExpirienceTrust,
                    double groupExpirienceTrust);

    double GetSelfTrust() const;
    double GetSelfExpirienceTrust() const;
    double GetGroupExpirienceTrust() const;

private:
    double _inertion;
    double _selfExpirienceTrust;
    double _groupExpirienceTrust;
};

#endif // PARTICLEFACTORS_H
