
#include <iostream>
#include <cstring>

#include "bestfitML.h"
#include "event.h"
#include "loadbalancer.h"

BestFitMLBalancer::BestFitMLBalancer(Controller *controller) {
    this->controller = controller;
    this->time_start = 0;
    this->numNodes = 0;
}

void BestFitMLBalancer::runPickle(std::string pickleFile, std::string networkFile, int numSamples) {
    int nodeID = 0;                 // Used to assign events to a specific node
    PickleLoader ploader;
    int pickleLength =  ploader.loadPickle(pickleFile);     // Load in specified pickle

    // Initialize discrete time variables for the controller (Specific to the data in pickleFile)
    initializeDiscreteTime(ploader, pickleFile, pickleLength, numSamples);

    // Initialize Machine Learning model
    // Sklearn ml_model; -> created in header, but may need initialized here instead
    ml_model.loadNetwork(networkFile);

    for (int i = 0; i < pickleLength; i++) {
        PickleData element = ploader.itemAtIndex(pickleFile, i);
        if (element.isWrite) {
            nodeID = findPredictiveBestFit(ploader, pickleFile, element, i);
            controller->addEvent(Event(element.size, nodeID, DISKWRITE, element.timestamp - time_start));    
        }
    }
}

/*
    Takes a PickleData object and determines the best 
*/
int BestFitMLBalancer::findPredictiveBestFit(PickleLoader ploader, std::string pickleFile, PickleData element, int index) {
    // Get prediction of next resource request
    std::string prediction = ml_model.getPredictionByEventNumber(ploader, pickleFile, 180);
    int predictSize = translatePrediction(prediction);

    std::vector<int> requests;
    requests.push_back(element.size);
    requests.push_back(predictSize);
    // Pull in current controller load
    return sizeFit(requests, controller->extractCurrentLoad()).front();
}

int BestFitMLBalancer::translatePrediction(std::string prediction) {
    if (!prediction.compare("small")) {
        return 2048;
    }
    if (!prediction.compare("medium")) {
        return 4096;
    }
    if (!prediction.compare("large")) {
        return 16384;
    }
    if (!prediction.compare("huge")) {
        return 131072;
    }
    return 300000;
}


void BestFitMLBalancer::initializeDiscreteTime(PickleLoader ploader, std::string pickleFile, int pickleLength, int numSamples) {
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











std::vector<int> BestFitMLBalancer::sizeFit(std::vector<int> nextRequests, std::vector<int> bins)
{
    std::vector<int> locations(nextRequests.size(), 0);
    std::vector<int> sortedRequests = nextRequests;
    sort(sortedRequests.begin(), sortedRequests.end());
    
    for (unsigned i = sortedRequests.size(); i-- > 0;){
        int largestBinIndex = std::find(bins.begin(), bins.end(), *std::max_element(bins.begin(), bins.end())) - bins.begin();
        locations[find(sortedRequests.begin(), sortedRequests.end(), sortedRequests[i]) - sortedRequests.begin()] = largestBinIndex;
        bins[largestBinIndex] -= sortedRequests[i];
    }

    return locations;
}