// Author: Justin P. Finger
// Last Update: 11/6/2017

#include <fstream>

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
    this->nodeSize    = nodeSize;   // Track node disk size
    shutdown = false;               // Flag for joining threads

    // Initialize Databank
    databank = new DataBank(numNodes);

    // Initialize Thread Specific variables
    queueList = new std::queue<Event>[numThreads];      // Create work queue's
    queueLock = new std::mutex[numThreads];             // Create work queue locks
    cvList    = new std::condition_variable[numThreads];// Create manager thread condition variables
    threadBoundries = new int[numThreads];              // Tracks manager thread node ranges
    
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
        if (nodeID < threadBoundries[i]) {
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
*
*   PRECONDITION: All work that will be assigned to the controller has been assigned
*                 before shutdownController() is called.
**/
void Controller::shutdownController() {
    // Check that each managerThread thread has finished processing all events in their
    // individual work queue before setting shutdown to true and destroying the threads.
    for (int i = 0; i < numThreads; i++) {
        std::unique_lock<std::mutex> queuelock(queueLock[i]);
        while (!queueList[i].empty()) {
            cv.wait(queuelock);
        }
        queuelock.unlock();
    }

    // Set shutdown to true and signal all threads to terminate and join
    shutdown = true;
    for (int i = 0; i < numThreads; i++) {
        cvList[i].notify_all();
        tpool.at(i).join();
    }

    for (int i = 0; i < numNodes; i++) {
        nodeList[i].finalizeReport();
    }
    databank->exportData();
    delete [] queueList;
    delete [] queueLock;
    delete [] cvList;
    delete [] threadBoundries;
    delete [] nodeList;
    delete databank;
}

/**
*   Creates DiskNode instances and stores them in the vector nodeList
**/
void Controller::spawnNodes() {
    nodeList = new DiskNode[numNodes];
    // Initialize values of the nodes in nList
    for (int i = 0; i < numNodes; i++) {
        nodeList[i].instantiateDiskNode(nodeSize, i, databank);
    }
}

/**
*   Spawn the DiskNode Manager threads.
*
*   Note: Must use (&Controller) and pass 'this' as first parameter.
**/
void Controller::spawnThreads() {
    // Determine the number of nodes each thread must manage
    int range_size = numNodes / numThreads;

    // Debug printing
    #ifdef DEBUG
        std::cout << "Number of Nodes: " << numNodes << ", Number of Manager Threads: " << numThreads << ", Thread Range: " << range_size << " nodes" << std::endl;
    #endif

    int range_start = 0;
    int range_end = range_size;
    // Spawn the threadds and assign them partitions of the node array to manage
    for (int i = 0; i < numThreads - 1; i++) {
        threadBoundries[i] = range_end; // Track the end of each thread's partition: used for assiging work to threads
        tpool.push_back(std::thread(&Controller::managerThread, this, range_start, range_end, i));

        // Debug printing -> check thread ranges
        #ifdef DEBUG
            std::cout << "Thread " << i << ": range_start = " << range_start <<", range_end = " << range_end << std::endl;        
        #endif

        range_start = range_end;
        range_end += range_size;
    }
    // For last thread, handle different end of range
    range_end = numNodes;
    threadBoundries[numThreads - 1] = range_end;
    tpool.push_back(std::thread(&Controller::managerThread, this, range_start, range_end, numThreads - 1));

    // Debug printing -> check thread ranges
    #ifdef DEBUG
        std::cout << "Thread " << numThreads - 1 << ": range_start = " << range_start <<", range_end = " << range_end << std::endl;        
    #endif
}


void Controller::managerThread(int nodeRangeStart, int nodeRangeEnd, int id) {
    // Create a lock for this threads mutex
    std::unique_lock<std::mutex> queuelock(queueLock[id], std::defer_lock);
    bool taskAcquired = false;

    // Used to grab incoming events
    Event * event = (Event *) calloc(1, sizeof(Event));

    while (true) {//!shutdown) {
        queuelock.lock();
        //Wait until there is work to do
        while (!taskAcquired) { //&& !shutdown) {
            // If task queue is not empty, there is work to do
            if (!queueList[id].empty()) {
                event->copyValues(queueList[id].front());
                // If task at the top of the queue is for a node managed by this thread, grab it.
                if (event->getNodeID() >= nodeRangeStart && event->getNodeID() < nodeRangeEnd) {
                    queueList[id].pop();
                    taskAcquired = true;
                }
            }
            else {  // Task queue is empty, meaning no work to do
                // Notify Controller that all work for this thread is currently completed, check if
                // it is time to shut down and destroy
                cv.notify_all();
                if (shutdown) {
                    queuelock.unlock();
                    free(event);
                    return;
                }
            }
            if (!taskAcquired) {    // Wait until work is available if none was found
                cvList[id].wait(queuelock);
            }
        }
        queuelock.unlock();
        taskAcquired = false;

        // Process the event
        nodeList[event->getNodeID()].processEvent(*event);
    }
}

void Controller::printNodeValues(char * filename) {
    std::ofstream myfile;
    myfile.open(filename);
    for (int i = 0; i < numNodes; i++) {
        myfile << nodeList[i].getDiskUsed() << "\n";
    }
}

int Controller::getNodeValue(int index) {
    return nodeList[index].getDiskUsed();
}

void Controller::waitForResults() {
    // Check that each managerThread thread has finished processing all events in their
    // individual work queue before setting shutdown to true and destroying the threads.
    for (int i = 0; i < numThreads; i++) {
        std::unique_lock<std::mutex> queuelock(queueLock[i]);
        while (!queueList[i].empty()) {
            cv.wait(queuelock);
        }
        queuelock.unlock();
    }
}

void Controller::resetController() {
    for (int i = 0; i < numNodes; i++) {
        nodeList[i].resetDisk();
    }
}
void Controller::setReportInterval(int interval, int numSamples) {
    for (int i = 0; i < numNodes; i++) {
        nodeList[i].setReportInterval(interval, numSamples);
    }
}


std::vector<int> Controller::extractCurrentLoad() {
    //waitForResults();   // inefficient, but leaving it for now for saftey
    
    // Create vector containing current load on diskNodes
    std::vector<int> diskLoad;

    // Loop through nodes and grab load
    for (int i = 0; i < numNodes; i++) {
        diskLoad.push_back(nodeSize - nodeList[i].getDiskUsed());
    }

    return diskLoad;
}
