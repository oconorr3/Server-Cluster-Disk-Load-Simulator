// Author: Justin P. Finger
// Last Update: 11/4/2017
#include <iostream>
#include "controller.h"

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
    this->nodeSize    = nodeSize;   // Track node disk size
    shutdown = false;               // Flag for joining threads

    // Initialize Thread Specific variables
    queueList = new std::queue<Event>[numThreads];      // Create work queue's
    queueLock = new std::mutex[numThreads];             // Create work queue locks
    cvList    = new std::condition_variable[numThreads];// Create manager thread condition variables
    threadBoundries = new int[numThreads];                    // Tracks manager thread node ranges
    
    // Create Nodes
    spawnNodes();
    // Create Threads
    spawnThreads();
}

/**
*   Adds an event to the controller's queue of events.
**/
void Controller::addEvent(Event event) {
    int nodeID = event.getNodeID(); 
    
    // Identify which thread manages the node to which the event was assigned, and add 
    // the event to that thread's work queue
    for (int i = 0; i < numThreads; i++) {

        // Since threadBoundries are stored in ascending order, this will only pass for the thread
        // which manages the desired node
        if (nodeID <= threadBoundries[i]) {
            // Lock the threads work queue
            std::unique_lock<std::mutex> work_queue_lock(queueLock[i]);    
            queueList[i].push(event);
            work_queue_lock.unlock();

            // Notify the thread it has recieved work
            cvList[i].notify_all();     
            break;
        }
    }
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
    std::this_thread::sleep_for (std::chrono::seconds(5));
    // std::unique_lock<std::mutex> queuelock(Controller::lk);
    // while (!taskQueue.empty()) {
    //     cv.wait(queuelock);
    // }
    // queuelock.unlock();
    shutdown = true;
    cv.notify_all();
    for (int i = 0; i < numThreads; i++) {
        cvList[i].notify_all();
        tpool.at(i).join();
        std::cout << queueList[i].size() << std::endl;
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
        threadBoundries[i] = range_end; // Track the end of each thread's partition: used for assiging work to threads
        tpool.push_back(std::thread(&Controller::managerThread, this, range_start, range_end, i));
        range_start = range_end;
        range_end += range_size - 1;
    }
    // For last thread, handle different end of range
    threadBoundries[numThreads - 1] = range_end;
    tpool.push_back(std::thread(&Controller::managerThread, this, range_start, numNodes - 1, numThreads - 1));
}


void Controller::managerThread(int nodeRangeStart, int nodeRangeEnd, int id) {
    // Create a lock for this threads mutex
    std::unique_lock<std::mutex> queuelock(queueLock[id], std::defer_lock);
    bool taskAcquired = false;

    // Used to grab incoming events
    Event * event = (Event *) calloc(1, sizeof(Event));

    while (!shutdown) {
        queuelock.lock();
        //Wait until there is work to do
        while (!taskAcquired && !shutdown) {
            // If task queue is empty, there is no work to do
            if (!queueList[id].empty()) {
                event->copyValues(queueList[id].front());
                // If task at the top of the queue is for a node managed by this thread, grab it.
                if (event->getNodeID() >= nodeRangeStart && event->getNodeID() <= nodeRangeEnd) {
                    queueList[id].pop();
                    taskAcquired = true;
                }
            }
            if (!taskAcquired) {    // Wait until work is available if none was found
                cvList[id].wait(queuelock);
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
    std::ofstream myfile;
    myfile.open(filename);
    for (int i = 0; i < numNodes; i++) {
        myfile << nodeList[i].getDiskUsed() << "\n";
    }
}

