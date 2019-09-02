#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <iostream>
#include <string>

#include "ilog.h"

class ConsoleLogger : public ILog {

public:
    ConsoleLogger();
    ~ConsoleLogger();

    void LogInfo(std::string message);
    void LogWarning(std::string message);
    void LogError(std::string message);
};

#endif // CONSOLELOGGER_H
