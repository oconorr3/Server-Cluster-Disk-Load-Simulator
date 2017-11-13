// Author: Justin P. Finger

#include "roundrobinlb.h"
#include "event.h"

RoundRobinLBalancer::RoundRobinLBalancer(Controller *controller) {
    this->controller = controller;
    numNodes = controller->getNumNodes();
}

void RoundRobinLBalancer::run(int inputSize, bool fixedEventSize, int eventSize) {
    if (fixedEventSize) {
        runFixedSize(inputSize, eventSize);
    }
    else {
        runVariableSize(inputSize, eventSize);
    }
}

void RoundRobinLBalancer::runFixedSize(int inputSize, int eventSize) {
    int nodeID = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = i % numNodes;
        controller->addEvent(Event(eventSize, nodeID, DISKWRITE));
    }
}

void RoundRobinLBalancer::runVariableSize(int inputSize, int eventSize) {
    int nodeID = 0;
    int writeSize = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = i % numNodes;
        writeSize = generateEventSize(eventSize);
        controller->addEvent(Event(writeSize, nodeID, DISKWRITE));
        
    }
}

int RoundRobinLBalancer::generateEventSize(int eventSize) {
    return rand() % eventSize;
}