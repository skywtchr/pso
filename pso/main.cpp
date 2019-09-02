#include <iostream>
#include <vector>

#include "ilog.h"
#include "consolelogger.h"
#include "particle.h"
#include "swarm.h"

using namespace std;

double testFunc(std::vector<int>& input) {

    return std::pow(input[0],2) + std::pow(input[1],2) + 1;
}

int main() {

    ILog* logger = new ConsoleLogger();

    Swarm swarm(*logger, 30, 500, &testFunc, 2);
    swarm.Start();

    std::cout << "Press Enter to terminate" << std::endl;
    getchar();
}
