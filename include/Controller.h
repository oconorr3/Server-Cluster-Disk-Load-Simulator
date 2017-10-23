#ifndef CONTROLLER_H
#define CONTROLLER_H

// Header for the Controller. This class will be in charge of creating threads and assigning
// loads to the threads

#include <iostream>
#include <thread>
#include <vector>
#include <queue>

#include "Event.h"
#include "Node.h"

// Definition of the Controller Class
class Controller {    
    public:
        /* CONSTRUCTORS */
        Controller(int threads, int nodes, int nSize);

        /* PUBLIC FUNCTION DECLARATIONS */
        void addEvent(Event event);     // Adds an event to the taskQueue for the controller
        int getNumNodes();              // Returns the number of nodes 


    private:
        int numNodes;                   // Number of nodes to be simulated by the controller
        int numThreads;                 // Number of threads to be used by the controller
        int nodeSize;                   // The size (in bytes) of th disk capacity for a node
        Node * nlist;                   // Pointer to array of nodes tracked by the controller. Populated by spawnNodes()
        std::vector<std::thread> tpool; // Tracks the threads used by the Controller to track nodes
        std::queue<Event> taskQueue;    // Queue of tasks that the controller must distribute/manage

        /* PRIVATE FUNCTION DECLARATIONS */
        void spawnThreads();            // spawns the threads that manage the nodes
        void spawnNodes();              // creates all nodes that are tracked by the controller

        void managerThread(int nodeRangeStart, int nodeRangeEnd);
};

#endif
