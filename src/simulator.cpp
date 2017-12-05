#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "pickleloader.h"
#include "sklearn.h"
#include "variance_fit.h"

// #include <thread>         // std::this_thread::sleep_for
// #include <chrono>         // std::chrono::seconds
 
#include <iostream>

// For testing
int main() {
    Controller c(20, 10000, 550);
    RandomLoadBalancer lb(&c);
    lb.run(15000, true, 50);
    char file1[] = "time1.csv";
    c.printNodeValues(file1);
    //
    // lb.run(1500, true, 50);
    // char file2[] = "time2.csv";
    // c.printNodeValues(file2);
    //
    // lb.run(1500, true, 50);
    // char file3[] = "time3.csv";
    // c.printNodeValues(file3);
    //
    // lb.run(1500, true, 50);
    // char file4[] = "time4.csv";
    // c.printNodeValues(file4);
    //
    // lb.run(20000000, true, 50);
    // char file5[] = "time6.csv";
    // c.printNodeValues(file5);
    //
    //
    // c.shutdownController();

    // std::vector<PickleData> dataVector;

    // PickleLoader ploader;
    // int firstLength =  ploader.loadPickle("exclude/tracedata00.pkl");
    // for (int i = 0; i < firstLength; i++) {
    //     PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
    //     std::cout << element.size << std::endl;
    //     dataVector.push_back(element);
    // }

    // Sklearn sklearn;
    // sklearn.loadNetwork("sgd-modhuber.sklnetwork.pkl");
    // // std::cout << sklearn.getPrediction(dataVector) << std::endl;
    // std::cout << sklearn.getPredictionByEventNumber(ploader, "exclude/tracedata00.pkl", 180) << std::endl;

    // // Controller c(7, 10, 1000000);
    // // RoundRobinLBalancer lb(&c);
    // // lb.runPickle("exclude/tracedata00.pkl", 150);
    // // //lb.run(750, true, 500000);
    // // char file1[] = "time1.csv";
    // // c.printNodeValues(file1);
    // // // c.shutdownController(); 
    
    // Controller c(4, 10, 1000000);
    // VarianceFit lb(&c);
    // lb.runVarianceFit("exclude/tracedata00.pkl", 150);
    // //lb.run(750, true, 500000);
    // char file1[] = "time1.csv";
    // c.printNodeValues(file1);
    c.shutdownController(); 
    return 0;
}
