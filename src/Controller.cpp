#include "Controller.h"
#include "Node.h"

#include "Poco/Runnable.h"

Controller::Controller(int n) {

    nodepool.push_back(4);
    // Spawn our node instances as separate threads, track them in nodepool
    for (int i = 0; i < n; i++) {
        //Node *a = new Node(4, i);
       // nodepool.pushback(thread(a.run, NULL));
    }
    
}

int main() {
    return 0;
}