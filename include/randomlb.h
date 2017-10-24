#ifndef RANDOMLB_H
#define RANDOMLB_H

#include "controller.h"



class RandomLoadBalancer {
    public:
        RandomLoadBalancer(Controller *controller);

        void run(int inputSize, bool fixedEventSize, int eventSize);
    private:
        Controller *controller;
        int numNodes;

        void runFixedSize(int inputSize, int eventSize);
        void runVariableSize(int inputSize, int eventSize);

        int generateNodeID();
        int generateEventSize(int eventSize);
};

#endif