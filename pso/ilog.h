#ifndef ILOG_H
#define ILOG_H

#include <string>

class ILog {

public:
    virtual ~ILog() {}

    virtual void LogInfo(std::string message) = 0;
    virtual void LogWarning(std::string message) = 0;
    virtual void LogError(std::string message) = 0;
};

#endif // ILOG_H
