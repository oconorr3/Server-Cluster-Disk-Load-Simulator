#ifndef CONTROLLER_H
#define CONTROLLER_H

// Header for the Controller. This class will be in charge of creating threads and assigning
// loads to the threads
#include <thread>
#include <iostream>
#include <vector>

class Controller {
    int numNodes;

    
    public:

        /*PUBLIC FUNCTION DECLARATIONS*/

    private:
        vector<thread> nodepool;

        /* PRIVATE FUNCTION DECLARATIONS */
        bool spawnNodes(int n); 
}

#endif
