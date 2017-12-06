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

// For testing
int main() {
    Controller c(1, 1000, 2000000);
    RoundRobinLBalancer lb(&c);
    lb.runPickle("exclude/tracedata00.pkl",150);// "exclude/sgd-modhuber.sklnetwork.pkl", 150);

    char file[] = "mlEndState.csv";
    c.printNodeValues(file);
    c.shutdownController(); 
    return 0;
}