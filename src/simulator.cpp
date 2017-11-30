#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "pickleloader.h"
// #include "sklearn.h"

#include <iostream>

// For testing
int main() {
<<<<<<< HEAD
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
    c.shutdownController();

=======
    Controller c(20, 1000, 1000000);
    RoundRobinLBalancer lb(&c);

    lb.runPickle("exclude/tracedata00.pkl");

    char file1[] = "time1.csv";
    c.printNodeValues(file1);

    c.shutdownController();

>>>>>>> 791229edefd062f42721bcb911aa00bb5c6fda43
    // PickleLoader ploader;
    // int firstLength =  ploader.loadPickle("exclude/tracedata00.pkl");
    // for (int i = 0; i < firstLength; i++) {
    //     PickleData element = ploader.itemAtIndex("exclude/tracedata00.pkl", i);
    //     std::cout << element.timestamp << " " << element.elapsedTime << " " << element.isWrite <<
    //         " " << element.fileName << " " << element.diskNum << " " << element.size << std::endl;
    // }
    
    return 0;
}
