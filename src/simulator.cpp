#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "pickleloader.h"
// #include "sklearn.h"
#include "variance_fit.h"

// #include <thread>         // std::this_thread::sleep_for
// #include <chrono>         // std::chrono::seconds
 
#include <iostream>

// For testing
int main() {
    // Controller c(7, 10, 1000000);
    // RoundRobinLBalancer lb(&c);
    // lb.runPickle("exclude/tracedata00.pkl", 150);
    // //lb.run(750, true, 500000);
    // char file1[] = "time1.csv";
    // c.printNodeValues(file1);
    // // c.shutdownController(); 
    
    Controller c(4, 10, 1000000);
    VarianceFit lb(&c);
    lb.runVarianceFit("exclude/tracedata00.pkl", 150);
    //lb.run(750, true, 500000);
    char file1[] = "time1.csv";
    c.printNodeValues(file1);
    c.shutdownController(); 
    return 0;
}
