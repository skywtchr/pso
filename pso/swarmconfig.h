#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H


class SwarmConfig
{
public:
    SwarmConfig();

    int particlesCount;
    int iterationCount;

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
