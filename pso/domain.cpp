#include "domain.h"

Domain::Domain(double lowerLimit,
               double upperLimit)
{
    _lowerLimit = lowerLimit;
    _upperLimit = upperLimit;
}

double Domain::GetLowerLimit() const
{
    return _lowerLimit;
}

double Domain::GetUpperLimit() const
{
    return _upperLimit;
}
