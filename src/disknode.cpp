#include <iostream>

#include "disknode.h"

DiskNode::DiskNode(int diskSize, int nodeID) {
    this->diskSize = diskSize;
    this->nodeID   = nodeID;
    this->diskUsed = 0;
    this->databank = NULL;
    lru_threshold  = ((diskSize * 70) / 100);  // 70% of disk space (NOTE: Maybe make this a parameter?)
    timestamp = 0;
    reportInterval = 0;
    nextReportTime = 0;
    samplesProcessed = 0;
    totalSamples = 0;
    
}

void DiskNode::instantiateDiskNode(int diskSize, int nodeID, DataBank *databank) {
    this->diskSize = diskSize;
    this->nodeID   = nodeID;
    this->diskUsed = 0;
    this->databank = databank;
    lru_threshold  = ((diskSize * 70) / 100);  // 70% of disk space (NOTE: Maybe make this a parameter?)    
    timestamp = 0;
    reportInterval = 0;
    nextReportTime = 0;
    samplesProcessed = 0;
    totalSamples = 0;
}
/**
 * Determine which function to call based on type of event
 */
bool DiskNode::processEvent(Event event) {

    //std::cout << "HERE" << std::endl;
    // Update time counter
    if (!updateTime(event.getTimestamp())) {
        return false;
    }
 
    // Might be necessary to check whether event ID
    // matches DiskNode id, currently no way to get event id
    enum EventType type = event.getEventType();
    if (type == DISKREAD) {
        return processDiskRead();
    }
    else if (type == DISKWRITE) {
        // if (nodeID == 115) {
        //     std::cout << "Disk Load Before Write: " << diskUsed << std::endl;
        // }
        processDiskWrite(event.getEventSize());
        // if (nodeID == 115) {
        //     std::cout << "After Write: " << diskUsed << std::endl;
        // }
        return true;
    }
    else {
        return false;
    }

    
}

/**
 * Remove previous request to make space for next request
 */
void DiskNode::runLRU(int requestSize) {
    int targetDiskUsed = diskSize - requestSize;
    if (targetDiskUsed > lru_threshold) {
        targetDiskUsed = lru_threshold;
    }

    while (diskUsed > targetDiskUsed) {
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
    if (size >= diskSize || size == 0) {
        return false;
    }
    // Ensure the write will not overflow the disk (clean space)
    if ((diskUsed + size) > diskSize) {
        runLRU(size);
        diskUsed += size;
        filesOnDisk.push_back(size);
    }
    else {
        
        diskUsed += size;
     filesOnDisk.push_back(size);
    }
    return true;
}

/**
*   Returns the amount of the nodes "disk" that is in use
**/
int DiskNode::getDiskUsed() {
    return diskUsed;
}

void DiskNode::resetDisk() {
    diskUsed = 0;
    timestamp = 0;
    nextReportTime = 0;
    samplesProcessed = 0;
}

void DiskNode::setReportInterval(int interval, int numSamples) {
    reportInterval = interval;
    totalSamples = numSamples + 1;
}

bool DiskNode::updateTime(int eventTime) {
    if (eventTime < timestamp) {
        return false;
    }

    timestamp = eventTime;
    
    while (timestamp > nextReportTime && samplesProcessed < totalSamples) {
        samplesProcessed++;
        databank->logData(nodeID, diskUsed);
        nextReportTime += reportInterval;
    }
    return true;
}

void DiskNode::finalizeReport() {
    while (samplesProcessed < totalSamples + 1) {
        databank->logData(nodeID, diskUsed);
        samplesProcessed++;
    }
}
