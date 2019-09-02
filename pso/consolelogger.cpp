#include "consolelogger.h"

ConsoleLogger::ConsoleLogger() {

}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::LogInfo(std::string message) {
    std::cout << "INFO: " << message << std::endl;
}

void ConsoleLogger::LogWarning(std::string message) {
    std::cout << "WARN: " << message << std::endl;
}

void ConsoleLogger::LogError(std::string message) {
    std::cout << "ERROR: " << message << std::endl;
}
