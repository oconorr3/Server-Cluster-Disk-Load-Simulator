// Author: Justin P. Finger

#include "randomlb.h"
#include "event.h"

/*
    Creates a Random load balancer that uses a specified controller
*/
RandomLoadBalancer::RandomLoadBalancer(Controller *controller) {
    this->controller = controller;
    numNodes = controller->getNumNodes();
}

/*
    Runs the load balancer for a specified number of events. This method has two variants,
    one with fixed event (disk write) size, and one with random event sizes. This is toggled
    via the fixedEventSize parameter.

    Parameters:
        inputSize      - The number of events to generate/run
        fixedEventSize - If true, all events will be of eventSize, else they will be randomly
                            generated sizes from 0 to eventSize.
        eventSize      - The size threshold of generated events.
*/
void RandomLoadBalancer::run(int inputSize, bool fixedEventSize, int eventSize) {
    if (fixedEventSize) {
        runFixedSize(inputSize, eventSize);
    }
    else {
        runVariableSize(inputSize, eventSize);
    }
}

/*
    Runs the fixed event size variant of the load balancer. 

    Parameters:
        inputSize - The number of events to generate/run
        eventSize - The size of each event
*/
void RandomLoadBalancer::runFixedSize(int inputSize, int eventSize) {
    int nodeID = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = generateNodeID();
        controller->addEvent(Event(eventSize, nodeID, DISKWRITE));
    }
}

/*
    Runs the variable event size variant of the load balancer. Event sizes will be between
    0 and eventSize.
    Parameters:
        inputSize - The number of events to generate/run
        eventSize - The maximum size possible for events to be generated
*/
void RandomLoadBalancer::runVariableSize(int inputSize, int eventSize) {
    int nodeID = 0;
    int bytes = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = generateNodeID();
        bytes = generateEventSize(eventSize);
        controller->addEvent(Event(bytes, nodeID, DISKWRITE));

    }
}

/*
    Generates a random number between 0 and numNodes
*/
int RandomLoadBalancer::generateNodeID() {
    return rand() % numNodes;
}

/*
    Generates a random number between 0 and eventSize
*/
int RandomLoadBalancer::generateEventSize(int eventSize) {
    return rand() % eventSize;
}