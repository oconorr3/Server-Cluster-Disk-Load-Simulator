// Author: Justin P. Finger

#include "event.h"
#include "pickleloader.h"
#include "roundrobinlb.h"

/*** Public Methods ***/
/*
    Creates a Round Robin load balancer that uses a specified controller
*/
RoundRobinLBalancer::RoundRobinLBalancer(Controller *controller) {
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
void RoundRobinLBalancer::run(int inputSize, bool fixedEventSize, int eventSize) {
    if (fixedEventSize) {
        runFixedSize(inputSize, eventSize);
    }
    else {
        runVariableSize(inputSize, eventSize);
    }
}

/*
    Runs the load balancer on a specified pickle file containing disk event data. 

    Parameters:
        pickleFile - String specifying the path/filename of the pickle file containing
                     the data to be run through the load balancer.
*/
void RoundRobinLBalancer::runPickle(std::string pickleFile) {
    PickleLoader ploader;
    int pickleLength =  ploader.loadPickle(pickleFile);
    int nodeID = 0;
    for (int i = 0; i < pickleLength; i++) {
        PickleData element = ploader.itemAtIndex(pickleFile, i);
        if (element.isWrite) {  
            nodeID = i % numNodes;
            controller->addEvent(Event(element.size, nodeID, DISKWRITE));
        }
    }
}

/*** Private Methods ***/
/*
    Runs the fixed event size variant of the load balancer. 

    Parameters:
        inputSize - The number of events to generate/run
        eventSize - The size of each event
*/
void RoundRobinLBalancer::runFixedSize(int inputSize, int eventSize) {
    int nodeID = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = i % numNodes;
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
void RoundRobinLBalancer::runVariableSize(int inputSize, int eventSize) {
    int nodeID = 0;
    int writeSize = 0;
    for (int i = 0; i < inputSize; i++) {
        nodeID = i % numNodes;
        writeSize = generateEventSize(eventSize);
        controller->addEvent(Event(writeSize, nodeID, DISKWRITE));
        
    }
}

/*
    Generates a random number between 0 and eventSize
*/
int RoundRobinLBalancer::generateEventSize(int eventSize) {
    return rand() % eventSize;
}