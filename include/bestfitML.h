#ifndef BESTFITML_H
#define BESTFITML_H

#include "controller.h"
#include "pickleloader.h"



class BestFitMLBalancer {
    public:
        BestFitMLBalancer(Controller *controller);

        runPickle(std::string pickleFile, int numSamples);
    private:
        Controller *controller;
        int time_start;

        initializeDiscreteTime(PickleLoader ploader, std::string pickleFile, int pickleLength, int numSamples);

};
#endif