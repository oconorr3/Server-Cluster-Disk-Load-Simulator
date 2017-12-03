#ifndef ROUNDROBINLB_H
#define ROUNDROBINLB_H

#include "controller.h"



class RoundRobinLBalancer {
    public:
        /*
         Creates a Round Robin load balancer that uses a specified controller
         */
        RoundRobinLBalancer(Controller *controller);

        /*
        Runs the load balancer for a specified number of events. This method has two variants,
        one with fixed event (disk write) size, and one with random event sizes. This is toggled
        via the fixedEventSize parameter.

        Parameters:
            inputSize      - The number of events to generate/run
            fixedEventSize - If true, all events will be of eventSize, else they will be randomly
                             generated sizes from 0 to eventSize.
            eventSize      - The size threshold of generated events.
        */
        void run(int inputSize, bool fixedEventSize, int eventSize);

        /*
        Runs the load balancer on a specified pickle file containing disk event data. 

        Parameters:
            pickleFile - String specifying the path/filename of the pickle file containing
                         the data to be run through the load balancer.
        */
        void runPickle(std::string pickleFile, int numSamples);
    private:
        Controller *controller;     // Controller to be used by the load balancer
        int numNodes;               // The number of nodes managed by the controller
        int time_start;             // Starting timestamp of dataset for discrete time
        int time_end;               // Ending timestamp of dataset for discrete time

        /* PRIVATE FUNCTIONS */
        
        /*
        Runs the fixed event size variant of the load balancer. 

        Parameters:
            inputSize - The number of events to generate/run
            eventSize - The size of each event
        */
        void runFixedSize(int inputSize, int eventSize);

        /* PRIVATE FUNCTIONS */
        
        /*
        Runs the fixed event size variant of the load balancer. 

        Parameters:
            inputSize - The number of events to generate/run
            eventSize - The size of each event
        */
        void runVariableSize(int inputSize, int eventSize);

        /*
        Generates a random number between 0 and eventSize
        */
        int generateEventSize(int eventSize);
};

#endif