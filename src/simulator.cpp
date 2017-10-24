#include "controller.h"
#include "randomlb.h"

#include <iostream>
int main() {
    Controller c(5, 1000, 550);
    RandomLoadBalancer lb(&c);
    lb.run(20000, true, 50);
    c.shutdownController();
    c.printNodeValues();
    return 0;
}
