#ifndef NODE_H
#define NODE_H

// Defines the Node class

class Node{
    int diskSize, diskUsed;
public:
    Node(int size);
    void diskWrite(int writeSize);
}

#endif