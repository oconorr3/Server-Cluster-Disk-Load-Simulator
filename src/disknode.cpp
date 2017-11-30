#include <iostream>

#include "disknode.h"

DiskNode::DiskNode(int diskSize, int nodeID) {
    this->diskSize = diskSize;
    this->nodeID   = nodeID;
    this->diskUsed = 0;
    lru_threshold  = ((diskSize * 30) / 100);  // 70% of disk space (NOTE: Maybe make this a parameter?)
    lru_disk_free  = diskSize - lru_threshold; // Exact amount of disk free when disk is filled to lru_threshold
}

void DiskNode::instantiateDiskNode(int diskSize, int nodeID) {
    this->diskSize = diskSize;
    this->nodeID   = nodeID;
    this->diskUsed = 0;
    lru_threshold  = ((diskSize * 70) / 100);  // 70% of disk space (NOTE: Maybe make this a parameter?)    
    lru_disk_free  = diskSize - lru_threshold; // Exact amount of disk free when disk is filled to lru_threshold
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
    int spaceNeeded = size - (diskSize - diskUsed);
    // Clean up diskUsed to match space needed or the disk usage defined by lru_disk_free, whichever is larger
    if (spaceNeeded < lru_disk_free) {
        spaceNeeded = lru_disk_free;        // Free at least to 70% disk usage
    }
    // Remove previous requests using LRU until previous condition is met
    while (spaceNeeded > (diskSize - diskUsed)) {
        int removedValue = filesOnDisk.front();
        filesOnDisk.pop_front();
        diskUsed -= removedValue;
    }
}

/**
 *  Process disk read event
 */
bool DiskNode::processDiskRead() {
    // TODO: Handle this when timing is implemented
    return true;
}

/**
 *  Process disk write event
 */
bool DiskNode::processDiskWrite(int size) {
    // Ensure size is not larger than total disk space
    if (size > diskSize || size == 0) {
        return false;
    }
    // Ensure the write will not overflow the disk (clean space)
    if ((diskUsed + size) > diskSize) {
        runLRU(size);
    }
    diskUsed += size;
    filesOnDisk.push_back(size);
    return true;
}

/**
*   Returns the amount of the nodes "disk" that is in use
**/
int DiskNode::getDiskUsed() {
    return diskUsed;
}
