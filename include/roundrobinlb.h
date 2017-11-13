#ifndef ROUNDROBINLB_H
#define ROUNDROBINLB_H

#include "controller.h"



class RoundRobinLBalancer {
    public:
        RoundRobinLBalancer(Controller *controller);

        void run(int inputSize, bool fixedEventSize, int eventSize);
    private:
        Controller *controller;
        int numNodes;

        void runFixedSize(int inputSize, int eventSize);
        void runVariableSize(int inputSize, int eventSize);

        int generateEventSize(int eventSize);
};

#endif