#ifndef DiskNode_H
#define DiskNode_H

#include <list>

#include "event.h"

// Defines the DiskNode class
class DiskNode {
public:
    DiskNode() { }; // Default Constructor
    DiskNode(int diskSize, int DiskNodeID);

    void instantiateDiskNode(int diskSize, int DiskNodeID);
    /**
    Determines if the event is a disk read or write, and calls the appropriate
    private methods to handle that type.

    NOTE: this could be changed to a bool to handle requests bigger than total disk size
    **/
    bool processEvent(Event event);

    /**
    * Returns the amount of the DiskNodes "disk" that is in use
    **/
    int getDiskUsed();


private:
    /* PRIVATE VARIABLE DECLARATIONS */
    int diskSize;                   // The total disk space available
    int diskUsed;                   // The bytes used on the disk
    int nodeID;                     // ID of the DiskNode
    std::list<int> filesOnDisk;     // List of previous write sizes still stored on the disk

    /* PRIVATE FUNCTION DECLARATIONS */
    void runLRU(int size);          // Clears space on the disk using LRU
    bool processDiskRead();         // Not sure what we want to do for reads yet.
    bool processDiskWrite(int size);// Increment counter of disk space, update filesOnDisk, call LRU if not enough space


};

#endif
