#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include <vector>
#include <stdexcept>

#include "ilog.h"

class ObjectiveFunction
{
public:
    ObjectiveFunction(ILog &logger,
                      double (*objectiveFunction)(std::vector<int>&),
                      int variablesCount);

    double GetResult(std::vector<int>& input);
    int GetVariablesCount();

private:
    double (*_objectiveFunction)(std::vector<int>&);
    ILog *_logger;
    int _variablesCount;

    void ValidateInputSize(std::vector<int>& input);
};

#endif // OBJECTIVEFUNCTION_H
