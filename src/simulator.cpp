#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "pickleloader.h"
// #include "sklearn.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
#include <iostream>

// For testing
int main() {
    Controller c(2, 8, 1000000);
    RandomLoadBalancer lb(&c);
    lb.runPickle("exclude/tracedata00.pkl", 150);
    std::this_thread::sleep_for (std::chrono::seconds(5));
    char file1[] = "time1.csv";
    c.printNodeValues(file1);
    
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


    c.shutdownController();    
    return 0;
}
