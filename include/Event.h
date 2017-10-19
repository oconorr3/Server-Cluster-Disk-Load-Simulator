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
        Event(int eventSize, int node);

        /* PUBLIC METHOD DECLARATIONS */
        int getEventSize();

    private:
        int size;           // Size of the event (in bytes)
        int nodeNum;        // Numerical identifier of the node to which this event is assigned
        EventType type;     // The type of the event (disk read or write)
};

#endif