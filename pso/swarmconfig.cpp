#include "swarmconfig.h"

SwarmConfig::SwarmConfig()
{
    SetDefaultValues();
}

void SwarmConfig::SetDefaultValues()
{
    particlesCount = 30;
    iterationCount = 500;
}
