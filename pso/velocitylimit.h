#ifndef VELOCITYLIMIT_H
#define VELOCITYLIMIT_H

enum VelocityLimitMode {
    StandardLimit,
    LenghtLimit
};

class VelocityLimit
{
public:
    VelocityLimit(double maxValue, VelocityLimitMode mode);

    double GetMaxValue() const;
    VelocityLimitMode GetMode();

private:
    double _maxValue;
    VelocityLimitMode _mode;
};

#endif // VELOCITYLIMIT_H
