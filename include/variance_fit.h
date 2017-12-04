#ifndef VARIANCEFIT_H
#define VARIANCEFIT_H

#include "controller.h"

float population_variance(float load[], float size);

class VarianceFit {
    public:

        VarianceFit(Controller *controller); 
        void run(int inputSize, bool fixedEventSize, int eventSize);
        void runVarianceFit(std::string pickleFile, int numSamples);

    private:
        Controller *controller;     // Controller to be used by the load balancer
        int numNodes;               // The number of nodes managed by the controller
        int time_start;             // Starting timestamp of dataset for discrete time
        int time_end;               // Ending timestamp of dataset for discrete time
};

#endif