#include "controller.h"
#include "randomlb.h"
#include "pickleloader.h"
// #include "sklearn.h"

#include <iostream>

// For testing
int main() {
    // Controller c(20, 10000, 550);
    // RandomLoadBalancer lb(&c);
    // lb.run(1500, true, 50);
    // char file1[] = "time1.csv";
    // c.printNodeValues(file1);
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

    PickleLoader ploader;
    int firstLength =  ploader.loadPickle("exclude/tracedata00.pkl");
    for (int i = 0; i < firstLength; i++) {
        PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
        std::cout << element.elapsedTime << " " << element.isWrite << " " << element.fileName
            << " " << element.diskNum << " " << element.size << std::endl;
    }
    int secondLength =  ploader.loadPickle("exclude/tracedata01.pkl");
    for (int i = 0; i < secondLength; i++) {
        PickleData element = ploader.itemAtIndex("exclude/tracedata01.pkl", i);
        std::cout << element.elapsedTime << " " << element.isWrite << " " << element.fileName
            << " " << element.diskNum << " " << element.size << std::endl;
    }

    return 0;
}
