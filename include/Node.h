#ifndef NODE_H
#define NODE_H

#include <list>

#include <Event.h>

// Defines the Node class
class Node {
public:
    Node(int size, int id);
    void processEvent(Event event);


private:
    /* PRIVATE VARIABLE DECLARATIONS */
    int diskSize;   
    int diskUsed;
    int nodeID;
    std::list<int> filesOnDisk;

    /* PRIVATE FUNCTION DECLARATIONS */
    void runLRU();
    void processDiskRead();
    void processDiskWrite(int size);


};

#endif