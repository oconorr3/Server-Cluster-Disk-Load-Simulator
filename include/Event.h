#ifndef EVENT_H
#define EVENT_H

// Enumeration defining event types
enum EventType {
    DISKREAD,
    DISKWRITE
};

class Event {
    public:
        /* CONSTRUCTORS */

        /**
        Constructor for an Event object. Event objects define a disk read or write
        that a node must process.

        PARAMETERS:
            bytes     - The size of the disk request in bytes
            node      - The numerical ID of the node to which this event is assigned
            eventType - The type of the event (DISKREAD or DISKWRITE)
        **/
        Event(int bytes, int node, EventType eventType);

        /**** PUBLIC METHOD DECLARATIONS ****/

        /**
        Returns the size in bytes of the disk read/write request
        **/
        int getEventSize();

        /**
        Returns the type of the event (DISKREAD or DISKWRITE)
        **/
        EventType getEventType();

    private:
        int size_b;         // Size of the event (in bytes)
        int nodeID;         // Numerical identifier of the node to which this event is assigned
        EventType type;     // The type of the event (disk read or write)
};

#endif