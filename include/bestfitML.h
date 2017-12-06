#ifndef BESTFITML_H
#define BESTFITML_H

#include "controller.h"
#include "pickleloader.h"
#include "sklearn.h"



class BestFitMLBalancer {
    public:
        BestFitMLBalancer(Controller *controller);

        void runPickle(std::string pickleFile, std::string networkFile, int numSamples);
    private:
        Controller *controller;
        int time_start;
        Sklearn ml_model;

        int findBestFit(std::string pickleFile, PickleData Element, int index);
        
        int translatePrediction(std::string prediction);

        void initializeDiscreteTime(PickleLoader ploader, std::string pickleFile, int pickleLength, int numSamples);

};
#endif