#include "Node.h"

Node::Node(int size, int id) {
    diskSize = size;
    nodeID = id;
}

/**
 * Determine which function to call based on type of event
 */
bool Node::processEvent(Event event) {
    // Might be necessary to check whether event ID
    // matches Node id, currently no way to get event id
    enum EventType type = event.getEventType()
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
void Node::runLRU(int size) {
    std::cout << "runLRU called!" << std::endl;
    int floor = ((diskSize * 30) / 100);
    int spaceNeeded = size - (diskSize - diskUsed);
    // Clean up diskUsed to match space needed or 70% usage, whichever is larger
    if (spaceNeeded < floor) {
        spaceNeeded = floor;
    }
    // Remove previous requests using LRU until previous condition is met
    while (spaceNeeded > (diskSize - diskUsed)) {
        removedValue = filesOnDisk.pop_front();
        diskUsed -= removedValue;
    }
}

/**
 * Process disk read event
 */
bool Node::processDiskRead() {
    std::cout << "processDiskRead called!" << std::endl;
    return true;
}

/**
 * Process disk write event
 */
bool Node::processDiskWrite(int size) {
    std::cout << "processDiskWrite called!" << std::endl;
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