#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include "pickleloader.h"
#include "controller.h"
#include "event.h"

int * nodes_list; // List of nodes

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

/**
 *  Check if two arrays are equivalent
 */
bool arrayEquals(int first[], int second[], int size) {
    for (int i = 0; i < size; i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Given number of nodes and requests, generate all possible combinations of requests to node
 */
int increment(int size, int modulo) {
    int i = 1;
    bool incrementing = true;
    while (incrementing) {
        nodes_list[size-i] += 1;
        if ((nodes_list[size-i] % modulo) > 0) {
            incrementing = false;
        }
        else {
            nodes_list[size-i] = nodes_list[size-i] % modulo;
            i += 1;
            if (i > size) {
                i = 1;
                incrementing = false;
            }
        }
    }
}

/**
 * Best fit for a load balancer
 */
// int main() {
//     PickleLoader ploader;
//     Controller controller(1, 10, 1000000);
//     int numEvents =  ploader.loadPickle("exclude/tracedata00.pkl");
//     int counter = 0;

//     int limit = 4;

//     // Count number of events in the pickle that is a write request
//     for (int i = 0; i < numEvents; i++) {
//         PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
//         if (element.isWrite) {
//             counter++;
//             if (counter > limit) { // TESTING
//                 break;
//             }
//         }
//     }

//     // Create an array to hold size of all write requests
//     int size_data[counter];
//     int index = 0;
//     for (int i = 0; i < numEvents; i++) {
//         PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
//         if (element.isWrite) {
//             size_data[index] = element.size;
//             index++;
//             if (index > limit) { // TESTING
//                 break;
//             }
//         }
//     }

//     // std::cout << "REQUESTS ";
//     // for (int i = 0; i < counter; i++) {
//     //     std::cout << size_data[i] << " ";
//     // }
//     // std::cout << "\n";
    
//     float bestVariance = 0; // Keep track of best variance
//     int start_comparison = 1;
//     int numNodes = controller.getNumNodes();
//     int zeroes[counter];
//     float best_load[numNodes]; // Keep track of best load distribution
//     Event currentEvents[counter];
//     Event bestEvents[counter];
//     for (int i = 0; i < counter; i++) { // Initialize zeroes array to have all zeroes
//         zeroes[i] = 0;
//     }
//     float curVariance = 0;
    
//     // Generate all node combinations
//     nodes_list = new int[counter];
//     for (int i = 0; i < counter; i++) {
//         nodes_list[i] = 0;
//     }

//     do {
//         for (int i = 0; i < counter; i++) {
//             Event e = Event(size_data[i], nodes_list[i], DISKWRITE);
//             controller.addEvent(e);
//             currentEvents[i] = Event(size_data[i], nodes_list[i], DISKWRITE);
            
//         }
//         controller.waitUntilDone();
//         //std::cout << "(" << size_data[i] << ", " << nodes_list[i] << ")";
//             //std::cout << "Sim state " << i << ": "; 
//             // for (int i = 0; i < controller.getNumNodes(); i++) {
//             //     std::cout << "[" << controller.getNodeValue(i) << ", "; 
//             // }
//             // std::cout << "]\n"; 
//         // std::cout << "\n";
//         float load[controller.getNumNodes()];

//         // std::cout << "Simulator state ";
//         for (int i = 0; i < controller.getNumNodes(); i++) {
//             load[i] = controller.getNodeValue(i);
//             // std::cout << load[i] << " "; 
//         }
//         // std::cout << "\n";

//         curVariance = population_variance(load, controller.getNumNodes());
//         // std::cout << "Variance " << curVariance << std::endl;
//         if (curVariance < bestVariance || start_comparison) {
//             bestVariance = curVariance;
//             for (int i = 0; i < numNodes; i++) {
//                 best_load[i] = load[i];
//             }
//             for (int i = 0; i < counter; i++) {
//                 bestEvents[i] = currentEvents[i];
//             }
//             start_comparison = 0;
//         }
//         increment(counter, numNodes);
//         controller.resetController();
//     } while (!arrayEquals(nodes_list, zeroes, counter));
//     std::cout << "Best Variance: " << bestVariance << std::endl;
//     std::cout << "Best Load Distribution: ";
//     for (int i = 0; i < numNodes; i++) {
//         std::cout << best_load[i] << " ";
//     }
//     std::cout << "\n";
//     delete []nodes_list;
//     controller.shutdownController();
// }
