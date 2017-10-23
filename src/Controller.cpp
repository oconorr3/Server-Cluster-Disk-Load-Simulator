// Author: Justin P. Finger
// Last Update: 10/18/2017
#include<iostream>
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
    spawnThreads();
}

void Controller::addEvent(Event event) {
	taskQueue.push(event);
}

/**
*   Creates Node instances and stores them in the vector nodeList
**/
void Controller::spawnNodes() {
    nlist = new Node[numNodes];
    for (int i = 0; i < numNodes; i++) {
        nlist[i].instantiateNode(numNodes, nodeSize);
    }
}

/**
*   Spawn the Node Manager threads. 
*
*   Note: Must use (&Controller) and pass 'this' as first parameter.
**/
void Controller::spawnThreads() {
    // Determine the number of nodes each thread must manage
    int range_size = numNodes / numThreads; 
    int range_start = 0;
    int range_end = range_size;
    for (int i = 0; i < numThreads - 1; i++) {
        tpool.push_back(std::thread(&Controller::managerThread, this, range_start, range_end));
        range_start = range_end + 1;
        range_end += range_size;
    }
    // For last thread, handle different end of range
    tpool.push_back(std::thread(&Controller::managerThread, this, range_start, numNodes - 1));
}


void Controller::managerThread(int nodeRangeStart, int nodeRangeEnd) {
    std::cout << "\n" << nodeRangeEnd << std::endl;
    while (true) {

    }
}

// Temporary main for compilation
int main() {
    Controller c(3, 10000, 1);
    while (true) {

    }
}
/*int main() {
    return 0;
}*/