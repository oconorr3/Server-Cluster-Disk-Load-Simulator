#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "bestfitML.h"
#include "pickleloader.h"
#include "sklearn.h"
#include "variance_fit.h"

// #include <thread>         // std::this_thread::sleep_for
// #include <chrono>         // std::chrono::seconds
 
#include <iostream>
#include <stdlib.h>
#include <string.h>

// Displays command line arguments
static void displayUsage(bool displayAll);

// For testing
int main(int argc, char *argv[]) {
    std::string ml_network = "exclude/sgd-modhuber.sklnetwork.pkl";
    char *pickleFile;
    int opt_char;   // used for getopt() result
    int numThreads = DEFAULT_NUM_THREADS;
    int numNodes   = DEFAULT_NUM_NODES;
    int diskSize   = DEFAULT_DISK_SIZE;
    int numSamples = DEFAULT_SAMPLE_NUM;
    char *loadbalancer;
    while ((opt_char = getopt (argc, argv, "hn:t:b:s:p:r:")) != -1)
    {
        switch (opt_char) {
            case 'h':
                displayUsage(true);
                return 0;
            case 'n':
                numNodes = atoi(optarg);
                break;
            case 't':
                numThreads = atoi(optarg);
                break;
            case 'b':
                loadbalancer = optarg;
                break;
            case 's':
                diskSize = atoi(optarg);
                break;
            case 'p':
                pickleFile = optarg;
                break;
            case 'r':
                numSamples = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "Unknown option given. Use the following for argument options: simulator -h\n");
                break;
        }
    }

    if (loadbalancer == NULL) {
        displayUsage(false);
        return 0;
    }

    if (pickleFile == NULL) {
        std::cout << "No trace file specified, please specify a trace file with -p. (Run \"simulator -h\" for usage)" << std::endl;
        return 0;
    }


    if (strcmp(loadbalancer, "rand") == 0) {
        Controller c(numThreads, numNodes, diskSize);
        RandomLoadBalancer lb(&c);
        std::cout << "Running Random Load Balancer..." << std::endl;
        lb.runPickle(pickleFile, numSamples);
        c.shutdownController(); 

    }
    else if (strcmp(loadbalancer, "rr") == 0) {
        Controller c(numThreads, numNodes, diskSize);
        RoundRobinLBalancer lb(&c);
        std::cout << "Running Round-Robin Load Balancer..." << std::endl;
        lb.runPickle(pickleFile, numSamples);
        c.shutdownController(); 
    }
    else if (strcmp(loadbalancer, "ml") == 0) {
        Controller c(numThreads, numNodes, diskSize);
        BestFitMLBalancer lb(&c);
        std::cout << "Running Machine Learning Load Balancer..." << std::endl;
        lb.runPickle(pickleFile, ml_network, numSamples);
        c.shutdownController(); 
    }
    else {
        std::cout << "The load balancer specified does not exist. See load balancer options below:" << std::endl;
        displayUsage(false);
    }

    return 0;
}

static void displayUsage(bool displayAll) {
    if (displayAll) {
        std::cout << "To run the simulator, at minimum the -p and -b flags must be set." << std::endl;
        std::cout << "Minimum Usage: simulator -b <load balancer> -p <pickle file>" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Argument options/usage:" << std::endl;
        std::cout << "  -h                      Show help: displays command line argument options" << std::endl;
        std::cout << " "<< std::endl;
        std::cout << "  -n <number of nodes>    Sets the number of nodes to be used by the Simulator, default is 1,000" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "  -t <number of threads>  Sets the number of threads to be used by the Simulator, default is 4" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "  -s <disk size>          Sets the size in bytes of the disks in the Simulator, default is 2,000,000" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "  -p <pickle file>        Specifies which pickled trace file to run through the load balancers" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "  -r <number of samples>  Sets the number of disk load samples to be taken during a run, default is 150" << std::endl;
        std::cout << " " << std::endl;
        std::cout << "  -b <load balancer>      Designates the load balancer to run, options are:"  << std::endl;
        std::cout << "                                  rand -> random load balancer" << std::endl;
        std::cout << "                                  rr   -> round-robin load balancer" << std::endl;
        std::cout << "                                  ml   -> machine learning load balancer" << std::endl;
    }
    else {
        std::cout << "Please specify which load blancer you wish to run the simulator with using the -b flag" << std::endl;
        std::cout << "Usage: simulator  -b <load balancer>      Designates the load balancer to run, options are:"  << std::endl;
        std::cout << "                                              rand -> random load balancer" << std::endl;
        std::cout << "                                              rr   -> round-robin load balancer" << std::endl;
        std::cout << "                                              ml   -> machine learning load balancer" << std::endl;
    }
}