#include "objectivefunction.h"

ObjectiveFunction::ObjectiveFunction(ILog &logger,
                                     double (*objectiveFunction)(std::vector<double>&),
                                     int variablesCount)
{
    _logger = &logger;
    _objectiveFunction = objectiveFunction;
    _variablesCount = variablesCount;
}

double ObjectiveFunction::GetResult(std::vector<double> &input)
{
    ValidateInputSize(input);
    return (*_objectiveFunction)(input);
}

int ObjectiveFunction::GetVariablesCount()
{
    return _variablesCount;
}

void ObjectiveFunction::ValidateInputSize(std::vector<double> &input)
{
    if (static_cast<int>(input.size()) != _variablesCount) {
        auto errorMsg = "Invalid input size.";
        _logger->LogError(errorMsg);
        throw std::invalid_argument(errorMsg);
    }
}
