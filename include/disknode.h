#ifndef DiskNode_H
#define DiskNode_H

#include <list>

#include "databank.h"
#include "event.h"

// Defines the DiskNode class
class DiskNode {
public:
    DiskNode() { }; // Default Constructor
    DiskNode(int diskSize, int DiskNodeID);

    void instantiateDiskNode(int diskSize, int DiskNodeID, DataBank *databank);
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

    void resetDisk();
    void setReportInterval(int interval, int numSamples);

    void finalizeReport();


private:
    /* PRIVATE VARIABLE DECLARATIONS */
    // Discrete time
    int timestamp;                  // The current time on the node
    int reportInterval;             // Load reporting interval in microseconds
    int nextReportTime;              // Time at which next load report must take place
    int samplesProcessed;
    int totalSamples;

    // Node management
    DataBank *databank;
    int diskSize;                   // The total disk space available
    int diskUsed;                   // The bytes used on the disk
    int nodeID;                     // ID of the node
    int lru_threshold;              // The disk usage level that runLRU() will clean full disks to  
    std::list<int> filesOnDisk;     // List of previous write sizes still stored on the disk

    /* PRIVATE FUNCTION DECLARATIONS */
    void runLRU(int size);          // Clears space on the disk using LRU
    bool processDiskRead();         // Increment's time counter if considering reads
    bool processDiskWrite(int size);// Increment counter of disk space, update filesOnDisk, call LRU if not enough space
    bool updateTime(int eventTime);


};

#endif
