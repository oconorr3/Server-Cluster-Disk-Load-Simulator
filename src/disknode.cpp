#include <iostream>

#include "disknode.h"

DiskNode::DiskNode(int diskSize, int nodeID) {
    this->diskSize = diskSize;
    this->nodeID = nodeID;
}

void DiskNode::instantiateDiskNode(int diskSize, int nodeID) {
    this->diskSize = diskSize;
    this->nodeID = nodeID;
}
/**
 * Determine which function to call based on type of event
 */
bool DiskNode::processEvent(Event event) {
    // Might be necessary to check whether event ID
    // matches DiskNode id, currently no way to get event id
    enum EventType type = event.getEventType();
    if (type == DISKREAD) {
        return processDiskRead();
    }
    else if (type == DISKWRITE) {
        return processDiskWrite(event.getEventSize());
    }
    else {
        return false;
    }
}

/**
 * Remove previous request to make space for next request
 */
void DiskNode::runLRU(int size) {
    //std::cout << "runLRU called!" << std::endl;
    int floor = ((diskSize * 30) / 100);
    int spaceNeeded = size - (diskSize - diskUsed);
    // Clean up diskUsed to match space needed or 70% usage, whichever is larger
    if (spaceNeeded < floor) {
        spaceNeeded = floor;
    }
    // Remove previous requests using LRU until previous condition is met
    while (spaceNeeded > (diskSize - diskUsed)) {
        int removedValue = filesOnDisk.front();
        filesOnDisk.pop_front();
        diskUsed -= removedValue;
    }
}

/**
 * Process disk read event
 */
bool DiskNode::processDiskRead() {
    std::cout << "processDiskRead called!" << std::endl;
    return true;
}

/**
 * Process disk write event
 */
bool DiskNode::processDiskWrite(int size) {
    //std::cout << "processDiskWrite called!" << std::endl;
    if (size > diskSize || size == 0) {
        return false;
    }
    if ((diskUsed + size) > diskSize) {
        runLRU(size);
    }
    diskUsed += size;
    filesOnDisk.push_back(size);
    return true;
}

int DiskNode::getDiskUsed() {
    return diskUsed;
}
