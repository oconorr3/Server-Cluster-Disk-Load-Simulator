#ifndef RANDOMLB_H
#define RANDOMLB_H

#include "controller.h"



class RandomLoadBalancer {
    public:
        /*
         Creates a Random load balancer that uses a specified controller
         */
        RandomLoadBalancer(Controller *controller); 

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
        void runPickle(std::string pickleFile);
    private:
        Controller *controller;     // Controller to be used by the load balancer
        int numNodes;               // The number of nodes managed by the controller

        /* PRIVATE FUNCTIONS */
        
        /*
        Runs the fixed event size variant of the load balancer. 

        Parameters:
            inputSize - The number of events to generate/run
            eventSize - The size of each event
        */
        void runFixedSize(int inputSize, int eventSize);

        /*
        Runs the variable event size variant of the load balancer. Event sizes will be between
        0 and eventSize.
        Parameters:
            inputSize - The number of events to generate/run
            eventSize - The maximum size possible for events to be generated
        */
        void runVariableSize(int inputSize, int eventSize);

        /*
        Generates a random number between 0 and numNodes
        */
        int generateNodeID();

        /*
        Generates a random number between 0 and eventSize
        */
        int generateEventSize(int eventSize);
};

#endif