#ifndef CONTROLLER_H
#define CONTROLLER_H

// Header for the Controller. This class will be in charge of creating threads and assigning
// loads to the threads

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "event.h"
#include "node.h"
#include <string>

// Definition of the Controller Class
class Controller {    
    public:
        /* CONSTRUCTORS */
        Controller(int numThreads, int numNodes, int nodeSize);

        /* PUBLIC FUNCTION DECLARATIONS */
        void addEvent(Event event);     // Adds an event to the taskQueue for the controller
        int getNumNodes();              // Returns the number of nodes 
        void shutdownController();      // Joins all threads used by the controller once they have completed processing
        void printNodeValues(char * filename);         // Prints the values of nodes in nodeID order


    private:
        bool shutdown;
        int numNodes;                   // Number of nodes to be simulated by the controller
        int numThreads;                 // Number of threads to be used by the controller
        int nodeSize;                   // The size (in bytes) of th disk capacity for a node
        Node * nodeList;                // Pointer to array of nodes tracked by the controller. Populated by spawnNodes()
        std::vector<std::thread> tpool; // Tracks the threads used by the Controller to track nodes
        std::queue<Event> taskQueue;    // Queue of tasks that the controller must distribute/manage
        std::mutex lk;                  // Mutex used to lock and guard access to the taskQueue
        std::condition_variable cv;     // Condition variable used to synchronise and signal task queue availability
        std::queue<Event> *queueList;
        std::mutex *queueLock;
        int *boundries;
        std::condition_variable *cvList;
        

        /* PRIVATE FUNCTION DECLARATIONS */
        void spawnThreads();            // spawns the threads that manage the nodes
        void spawnNodes();              // creates all nodes that are tracked by the controller

        void managerThread(int nodeRangeStart, int nodeRangeEnd, int id);
};

#endif
