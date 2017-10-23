#ifndef NODE_H
#define NODE_H

#include <list>

#include "event.h"

// Defines the Node class
class Node {
public:
    Node() { }; // Default Constructor
    Node(int size, int id);

    void instantiateNode(int size, int id);
    /**
    Determines if the event is a disk read or write, and calls the appropriate
    private methods to handle that type. 

    NOTE: this could be changed to a bool to handle requests bigger than total disk size
    **/
    bool processEvent(Event event);

    int getDiskUsed();


private:
    /* PRIVATE VARIABLE DECLARATIONS */
    int diskSize;                   // The total disk space available
    int diskUsed;                   // The bytes used on the disk
    int nodeID;                     // ID of the node
    std::list<int> filesOnDisk;     // List of previous write sizes still stored on the disk

    /* PRIVATE FUNCTION DECLARATIONS */
    void runLRU(int size);                  // Clears space on the disk using LRU
    bool processDiskRead();         // Not sure what we want to do for reads yet.
    bool processDiskWrite(int size);// Increment counter of disk space, update filesOnDisk, call LRU if not enough space


};

#endif
