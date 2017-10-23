// Author: Justin P. Finger
// Last Update: 10/18/2017

#include "../include/Controller.h"
#include "../include/Node.h"

/**
*   Constructor for a Controller
*   
*   PARAMETERS:
*       threads - the number of threads to be used by the controller
*       nodes   - the number of nodes that the controller will simulate
**/
Controller::Controller(int threads, int nodes, int nSize) {
    numThreads  = threads; // Track number of threads
    numNodes    = nodes;   // Track number of nodes
    nodeSize    = nSize;

    // Create Nodes
    spawnNodes();
}

void Controller::addEvent(Event event) {
	taskQueue.push(event);
}


void Controller::spawnNodes() {
    for (int i = 0; i < numNodes; i++) {
        nodeList.push_back(Node(nodeSize, i));
    }
}

void Controller::spawnThreads() {

}

// Temporary main for compilation
/*int main() {
    return 0;
}*/