// Author: Justin P. Finger

#include "randomlb.h"
#include "event.h"
RandomLoadBalancer::RandomLoadBalancer(Controller *controller) {
    this->controller = controller;
    numNodes = controller->getNumNodes();
}

void RandomLoadBalancer::run(int inputSize, bool fixedEventSize, int eventSize) {
    if (fixedEventSize) {
        runFixedSize(inputSize, eventSize);
    }
    else {
        runVariableSize(inputSize, eventSize);
    }
}

void RandomLoadBalancer::runFixedSize(int inputSize, int eventSize) {
    int nodeID = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = generateNodeID();
        controller->addEvent(Event(eventSize, nodeID, DISKWRITE));
    }
}


void RandomLoadBalancer::runVariableSize(int inputSize, int eventSize) {
    int nodeID = 0;
    int bytes = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = generateNodeID();
        bytes = generateEventSize(eventSize);
        controller->addEvent(Event(bytes, nodeID, DISKWRITE));

    }
}

int RandomLoadBalancer::generateNodeID() {
    return rand() % numNodes;
}

int RandomLoadBalancer::generateEventSize(int eventSize) {
    return rand() % eventSize;
}