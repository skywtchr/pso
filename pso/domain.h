#ifndef DOMAIN_H
#define DOMAIN_H


class Domain
{
public:
    Domain(double lowerLimit,
           double upperLimit);

    double GetLowerLimit() const;
    double GetUpperLimit() const;

private:
    double _lowerLimit;
    double _upperLimit;
};

#endif // DOMAIN_H
