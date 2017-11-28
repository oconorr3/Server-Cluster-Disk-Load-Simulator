#include "controller.h"
#include "randomlb.h"
#include "pickleloader.h"
// #include "sklearn.h"

#include <iostream>

// For testing
int main() {
    Controller c(20, 1000, 1000000);
    RandomLoadBalancer lb(&c);

    lb.runPickle("exclude/tracedata00.pkl");

    char file1[] = "time1.csv";
    c.printNodeValues(file1);

    c.shutdownController();

    // PickleLoader ploader;
    // int firstLength =  ploader.loadPickle("exclude/tracedata00.pkl");
    // for (int i = 0; i < firstLength; i++) {
    //     PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
    //     std::cout << element.timestamp << " " << element.elapsedTime << " " << element.isWrite <<
    //         " " << element.fileName << " " << element.diskNum << " " << element.size << std::endl;
    // }
    
    return 0;
}
