// Author: Justin P. Finger
// Last Update: 10/18/2017

#include "Controller.h"
#include "Node.h"

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
    spawnThreads();
}


/**
*   Creates Node instances and stores them in the vector nodeList
**/
void Controller::spawnNodes() {
    for (int i = 0; i < numNodes; i++) {
        nodeList.push_back(Node(nodeSize, i));
    }
}

/**
*   Spawn the Node Manager threads. 
*
*   Note: Must use (&Controller) and pass 'this' as first parameter.
**/
void Controller::spawnThreads() {
    for (int i = 0; i < numThreads; i++) {
        tpool.push_back(std::thread(&Controller::managerThread, this, 0, i));
    }
}


void Controller::managerThread(int nodeRangeStart, int nodeRangeEnd) {
    while (true) {

    }
}

// Temporary main for compilation
int main() {
    Controller c(2, 1, 1);
    while (true) {

    }
    return 0;
}