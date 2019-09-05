#ifndef SWARMCONFIG_H
#define SWARMCONFIG_H


class SwarmConfig
{
public:
    SwarmConfig();

    int _particlesCount;
    int _iterationCount;

private:
    void SetDefaultValues();
};

#endif // SWARMCONFIG_H
