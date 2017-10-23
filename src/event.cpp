// Author: Justin Finger
// Last Update: 10/19/2017

#include "event.h"

/**
    Constructor for an Event object. Event objects define a disk read or write
    that a node must process.

    PARAMETERS:
        bytes     - The size of the disk request in bytes
        node      - The numerical ID of the node to which this event is assigned
        eventType - The type of the event (DISKREAD or DISKWRITE)
**/
Event::Event(int bytes, int node, EventType eventType) {
    size_b = bytes;
    nodeID = node;
    type   = eventType;   
}

/**
    Returns the size in bytes of the disk read/write request
**/
int Event::getEventSize() {
    return size_b;
}

/**
    Returns the type of the event (DISKREAD or DISKWRITE)
**/
EventType Event::getEventType() {
    return type;
}

int Event::getNodeID() {
    return nodeID;
}

void Event::copyValues(Event e) {
    size_b = e.getEventSize();
    nodeID = e.getNodeID();
    type = e.getEventType();
}