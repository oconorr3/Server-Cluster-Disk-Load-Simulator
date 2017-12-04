#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include "variance_fit.h"
#include "pickleloader.h"
#include "controller.h"
#include "event.h"

VarianceFit::VarianceFit(Controller *controller) {
    this->controller = controller;
    numNodes = controller->getNumNodes();
    time_start = 0;
    time_end = 0;
    srand(time(0));
}

/**
 * Calculate the population variance of a load
 */
float population_variance(float load[], float size) {
    float variance = 0;
    float mean = 0;
    int i;
    for (i = 0; i < size; i++) {
        mean += load[i];
    }
    mean /= size;
    for (int j = 0; j < size; j++) {
        variance += pow((load[j] - mean), 2);
    }
    variance *= (1/size);
    return variance;
}

void VarianceFit::runVarianceFit(std::string pickleFile, int numSamples) {

    /**
     * JUSTIN'S CODE
     */
    int nodeID = 0;                 // Used to assign events to a specific node
    int sampleTimeInterval = 0;     // The discrete time interval (in microsecond) at which node Load samples are taken
    PickleLoader ploader;
    int numEvents =  ploader.loadPickle(pickleFile);     // Load in specified pickle 

    PickleData element = ploader.itemAtIndex(pickleFile, 0);     // Get time of first event
    time_start = element.timestamp;

    element = ploader.itemAtIndex(pickleFile, numEvents - 1); // Get time of the second event
    time_end = element.timestamp - time_start;//element.timestamp;
    time_start = 0;
    sampleTimeInterval = (time_end - time_start) / numSamples;     // Calculate discrete time sampling interval

    std::cout << "startTime: " << time_start << std::endl;
    std::cout << "endTime: " << time_end << std::endl;
    std::cout << "interval: " << sampleTimeInterval << std::endl;
    controller->setReportInterval(sampleTimeInterval, numSamples);

    /***
     * 
     *  START VARIANCE FIT
     */

    // Controller controller(1, 20, 100000);
    // int numEvents =  ploader.loadPickle("exclude/tracedata00.pkl");
    int counter = 0;
    int limit = 2; // Limit number of requests w/ 0 indexing

    // Count number of events in the pickle that is a write request
    for (int i = 0; i < numEvents; i++) {
        element = ploader.itemAtIndex(pickleFile, i);
        if (element.isWrite) {
            counter++;
            if (counter > limit) {
                break;
            }
        }
    }

    // Create an array to hold size of all write requests
    int size_data[counter];
    int timestamp_data[counter];
    int index = 0;
    for (int i = 0; i < numEvents; i++) {
        element = ploader.itemAtIndex(pickleFile, i);
        if (element.isWrite) {
            size_data[index] = element.size;
            timestamp_data[index] = element.timestamp - time_start;
            index++;
            if (index > limit) {
                break;
            }
        }
    }

    int best_variance = 0;
    int cur_variance = 0;
    int start_comparison = 1;
    int numNodes = controller->getNumNodes();
    int best_load[numNodes];
    Event best_event;
    Event list_best_event[counter];
    Event e;

    for (int i = 0; i < counter; i++) {
        list_best_event[i] = Event(0, 0, DISKREAD);
    }
    for (int i = 0; i < counter; i++) {
        for (int j = 0; j < numNodes; j++) {
            for (int k = 0; k < counter; k++) {
                if (list_best_event[k].getEventType() == DISKWRITE) {
                    controller->addEvent(list_best_event[k]);
                }
            }
            e = Event(size_data[i], j, DISKWRITE, timestamp_data[i]);
            controller->addEvent(e);
            controller->waitForResults();
            float load[numNodes];

            for (int k = 0; k < numNodes; k++) {
                load[k] = controller->getNodeValue(k);
            }

            cur_variance = population_variance(load, numNodes);

            // Check for best variance
            if (cur_variance < best_variance || start_comparison) {
                best_variance = cur_variance;
                best_event = e;
                for (int k = 0; k < numNodes; k++) {
                    best_load[k] = load[k];
                }
                start_comparison = 0;
            }
            controller->waitForResults();
            controller->resetController();
        }
        list_best_event[i] = best_event;
        start_comparison = 1;
    }
    std::cout << "Best Variance: " << best_variance << std::endl;
    std::cout << "Best Load Distribution: ";
    for (int i = 0; i < numNodes; i++) {
        std::cout << best_load[i] << " ";
    }
    std::cout << "\n";

    controller->waitForResults();
    controller->resetController();
    for (int i = 0; i < counter; i++) {
        if (list_best_event[i].getEventType() == DISKWRITE) {
            controller->addEvent(list_best_event[i]);
        }
    }
}
