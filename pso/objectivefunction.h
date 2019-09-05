#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include <vector>
#include <stdexcept>

#include "ilog.h"

class ObjectiveFunction
{
public:
    ObjectiveFunction(ILog &logger,
                      double (*objectiveFunction)(std::vector<double>&),
                      int variablesCount);

    double GetResult(std::vector<double>& input);
    int GetVariablesCount();

private:
    double (*_objectiveFunction)(std::vector<double>&);
    ILog *_logger;
    int _variablesCount;

    void ValidateInputSize(std::vector<double>& input);
};

#endif // OBJECTIVEFUNCTION_H
