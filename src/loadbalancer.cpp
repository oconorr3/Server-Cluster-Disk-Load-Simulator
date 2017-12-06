#include "loadbalancer.h"

#include <ctime>
#include <cstdlib>

void seedRandomNumbers() {
    srand(time(0));
}

int generateNodeID(int numNodes) {
    return rand() % numNodes;
}
