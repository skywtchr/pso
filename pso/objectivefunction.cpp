#include "objectivefunction.h"

ObjectiveFunction::ObjectiveFunction(ILog &logger,
                                     double (*objectiveFunction)(std::vector<int>&),
                                     int variablesCount)
{
    _logger = &logger;
    _objectiveFunction = objectiveFunction;
    _variablesCount = variablesCount;
}

double ObjectiveFunction::GetResult(std::vector<int> &input)
{
    ValidateInputSize(input);
    return (*_objectiveFunction)(input);
}

int ObjectiveFunction::GetVariablesCount()
{
    return _variablesCount;
}

void ObjectiveFunction::ValidateInputSize(std::vector<int> &input)
{
    if (static_cast<int>(input.size()) != _variablesCount) {
        auto errorMsg = "Invalid input size.";
        _logger->LogError(errorMsg);
        throw std::invalid_argument(errorMsg);
    }
}
