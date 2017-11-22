#ifndef NODE_H
#define NODE_H

#include <list>

#include "event.h"

// Defines the Node class
class Node {
public:
    // Default Constructor
    Node() { 
        lru_threshold = 0; // Default value is clean disk till empty
    };

    Node(int diskSize, int nodeID);

    void instantiateNode(int diskSize, int nodeID);
    /**
    Determines if the event is a disk read or write, and calls the appropriate
    private methods to handle that type. 

    NOTE: this could be changed to a bool to handle requests bigger than total disk size
    **/
    bool processEvent(Event event);

    /**
    * Returns the amount of the nodes "disk" that is in use
    **/
    int getDiskUsed();


private:
    /* PRIVATE VARIABLE DECLARATIONS */
    int diskSize;                   // The total disk space available
    int diskUsed;                   // The bytes used on the disk
    int nodeID;                     // ID of the node
    int lru_threshold;              // The disk usage level that runLRU() will clean full disks to
    int lru_disk_free;              // The exact amount of space free on disk if LRU cleans to lru_threshold     
    std::list<int> filesOnDisk;     // List of previous write sizes still stored on the disk

    /* PRIVATE FUNCTION DECLARATIONS */
    void runLRU(int size);          // Clears space on the disk using LRU
    bool processDiskRead();         // Increment's time counter if considering reads
    bool processDiskWrite(int size);// Increment counter of disk space, update filesOnDisk, call LRU if not enough space


};

#endif
