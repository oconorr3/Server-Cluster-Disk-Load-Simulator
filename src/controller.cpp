// Author: Justin P. Finger
// Last Update: 10/18/2017
#include<iostream>
#include "controller.h"

/**
*   Constructor for a Controller
*   
*   PARAMETERS:
*       numThreads - the number of threads to be used by the controller
*       numNodes   - the number of nodes that the controller will simulate
*       nodeSize   - the size (in bytes) of the disk space each node simulates
**/
Controller::Controller(int numThreads, int numNodes, int nodeSize) {
    this->numThreads  = numThreads; // Track number of threads
    this->numNodes    = numNodes;   // Track number of nodes
    this->nodeSize    = nodeSize;

    // Create Nodes
    spawnNodes();
    // Create Threads
    spawnThreads();
}

/**
*   Returns the number of nodes tracked by the Controller
**/
int Controller::getNumNodes() {
    return numNodes;
}

/**
*   Adds an event to the controller's queue of events.
**/
void Controller::addEvent(Event event) {
	taskQueue.push(event);
}

/**
*   Creates Node instances and stores them in the vector nodeList
**/
void Controller::spawnNodes() {
    nodeList = new Node[numNodes];
    // Initialize values of the nodes in nList
    for (int i = 0; i < numNodes; i++) {
        nodeList[i].instantiateNode(numNodes, nodeSize);
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
    int range_end = range_size - 1;
    // Spawn the threadds and assign them partitions of the node array to manage
    for (int i = 0; i < numThreads - 1; i++) {
        tpool.push_back(std::thread(&Controller::managerThread, this, range_start, range_end));
        range_start = range_end;
        range_end += range_size - 1;
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