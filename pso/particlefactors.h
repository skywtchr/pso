#ifndef PARTICLEFACTORS_H
#define PARTICLEFACTORS_H


class ParticleFactors
{
public:
    ParticleFactors(double GetSelfTrust,
                    double GetSelfExpirienceTrust,
                    double GetGroupExpirienceTrust);

    double GetSelfTrust() const;
    double GetSelfExpirienceTrust() const;
    double GetGroupExpirienceTrust() const;

private:
    double _selfTrust;
    double _selfExpirienceTrust;
    double _groupExpirienceTrust;
};

#endif // PARTICLEFACTORS_H
