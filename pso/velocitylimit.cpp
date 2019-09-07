#include "velocitylimit.h"

VelocityLimit::VelocityLimit(double maxValue, VelocityLimitMode mode)
{
    _maxValue = maxValue;
    _mode = mode;
}

double VelocityLimit::GetMaxValue() const
{
    return _maxValue;
}

VelocityLimitMode VelocityLimit::GetMode()
{
    return _mode;
}
