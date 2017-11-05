// Author: Justin P. Finger
// Last Update: 10/18/2017
#include<iostream>
#include "controller.h"


#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <fstream>

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
    shutdown = false;
    
    // Create Nodes
    spawnNodes();
    // Create Threads
    spawnThreads();
}

/**
*   Adds an event to the controller's queue of events.
**/
void Controller::addEvent(Event event) {
    std::unique_lock<std::mutex> queuelock(Controller::lk);
    taskQueue.push(event);
    //queuelock.unlock();
    cv.notify_all();
}

/**
*   Returns the number of nodes tracked by the Controller
**/
int Controller::getNumNodes() {
    return numNodes;
}

/**
*   Joins all manager threads once their work is completed.
*   NOTE: This could be optimized some with a different condition variable.
**/
void Controller::shutdownController() {
    std::unique_lock<std::mutex> queuelock(Controller::lk);
    while (!taskQueue.empty()) {
        cv.wait(queuelock);
    }
    queuelock.unlock();
    shutdown = true;
    cv.notify_all();
    for (int i = 0; i < numThreads; i++) {
        tpool.at(i).join();
    }
}

/**
*   Creates Node instances and stores them in the vector nodeList
**/
void Controller::spawnNodes() {
    nodeList = new Node[numNodes];
    // Initialize values of the nodes in nList
    for (int i = 0; i < numNodes; i++) {
        nodeList[i].instantiateNode(nodeSize, i);
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
    // Create a lock for mutex lk
    std::unique_lock<std::mutex> queuelock(Controller::lk, std::defer_lock);
    bool taskAcquired = false;

    Event * event = (Event *) calloc(1, sizeof(Event));

    while (!shutdown) {
        queuelock.lock();
        //Wait until there is work to do
        while (!taskAcquired && !shutdown) {
            // If task queue is empty, there is no work to do
            if (!taskQueue.empty()) {
                
                event->copyValues(taskQueue.front());
                // If task at the top of the queue is for a node managed by this thread, grab it.
                if (event->getNodeID() >= nodeRangeStart && event->getNodeID() <= nodeRangeEnd) {
                    taskQueue.pop();
                    taskAcquired = true;
                    cv.notify_all();
                }
            }
            if (!taskAcquired) {
                cv.wait(queuelock);
            }
        }
        queuelock.unlock();
        taskAcquired = false;

        if (!shutdown) { 
            // pass command to node
            nodeList[event->getNodeID()].processEvent(*event);
        }
    }
    free(event);
}

void Controller::printNodeValues(char * filename) {
    //std::this_thread::sleep_for (std::chrono::seconds(25));
    std::ofstream myfile;
    myfile.open(filename);
    for (int i = 0; i < numNodes; i++) {
        myfile << nodeList[i].getDiskUsed() << "\n";
    }
}

