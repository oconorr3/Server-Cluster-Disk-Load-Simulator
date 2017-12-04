#include "controller.h"
#include "randomlb.h"
#include "roundrobinlb.h"
#include "pickleloader.h"
// #include "sklearn.h"
#include "variance_fit.h"

#include <iostream>

// For testing
int main() {
    Controller c(1, 1000, 1000000);
    VarianceFit lb(&c);
    lb.runVarianceFit("exclude/tracedata00.pkl", 150);
    //lb.run(750, true, 500000);
    char file1[] = "time1.csv";
    c.printNodeValues(file1);
    c.shutdownController();    
    return 0;
}
