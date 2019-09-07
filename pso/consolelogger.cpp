#include "consolelogger.h"

ConsoleLogger::ConsoleLogger() {
    _mode = ConsoleLoggerMode::INFO;
}

ConsoleLogger::ConsoleLogger(ConsoleLoggerMode mode)
{
    _mode = mode;
}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::LogInfo(std::string message) {
    if (_mode != ConsoleLoggerMode::INFO) {
        return;
    }
    std::cout << "INFO: " << message << std::endl;
}

void ConsoleLogger::LogWarning(std::string message) {
    if (_mode != ConsoleLoggerMode::INFO && _mode != ConsoleLoggerMode::INFO) {
        return;
    }
    std::cout << "WARN: " << message << std::endl;
}

void ConsoleLogger::LogError(std::string message) {
    std::cout << "ERROR: " << message << std::endl;
}
