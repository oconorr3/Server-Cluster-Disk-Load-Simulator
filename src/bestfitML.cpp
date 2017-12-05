
#include <iostream>

#include "bestfitML.h"

BestFitMLBalancer::BestFitMLBalancer(Controller *controller) {
    this->controller = controller;
    this->time_start = 0;
    this->numNodes = 0;
}

BestFitMLBalancer::runPickle(std::string pickleFile, int numSamples) {
    int nodeID = 0;                 // Used to assign events to a specific node
    PickleLoader ploader;
    int pickleLength =  ploader.loadPickle(pickleFile);     // Load in specified pickle
    
    initializeDiscreteTime(ploader, pickleFile, pickleLength, numSamples);

    for (int i = 0; i < pickleLength; i++) {
        
    }
}

BestFitMLBalancer::initializeDiscreteTime(PickleLoader ploader, std::string pickleFile, int pickleLength, int numSamples) {
    int sampleTimeInterval = 0;     // The discrete time interval (in microsecond) at which node Load samples are taken

    PickleData element = ploader.itemAtIndex(pickleFile, 0);     // Get time of first event
    time_start = element.timestamp;

    element = ploader.itemAtIndex(pickleFile, pickleLength - 1); // Get time of the second event
    int time_end = element.timestamp - time_start;//element.timestamp;

    sampleTimeInterval = time_end / numSamples;     // Calculate discrete time sampling interval

    std::cout << "startTime: " << time_start << std::endl;
    std::cout << "endTime: " << time_end << std::endl;
    std::cout << "interval: " << sampleTimeInterval << std::endl;
    controller->setReportInterval(sampleTimeInterval, numSamples);
}