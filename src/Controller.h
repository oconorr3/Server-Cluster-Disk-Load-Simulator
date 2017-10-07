#ifndef CONTROLLER_H
#define CONTROLLER_H

// Header for the Controller. This class will be in charge of creating threads and assigning
// loads to the threads
#include <thread>
#include <iostream>
#include <vector>


class Controller {    
    public:

        /*PUBLIC FUNCTION DECLARATIONS*/
        Controller(int n);

    private:
        int numNodes;
        std::vector<int> nodepool;

        /* PRIVATE FUNCTION DECLARATIONS */
        void spawnNodes(int n);
};

#endif
