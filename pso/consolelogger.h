#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include <iostream>
#include <string>

#include "ilog.h"

enum ConsoleLoggerMode {
    INFO,
    WARN,
    ERROR
};

class ConsoleLogger : public ILog {

public:
    ConsoleLogger();
    ConsoleLogger(ConsoleLoggerMode mode);
    ~ConsoleLogger();

    void LogInfo(std::string message);
    void LogWarning(std::string message);
    void LogError(std::string message);

private:
    ConsoleLoggerMode _mode;
};

#endif // CONSOLELOGGER_H
