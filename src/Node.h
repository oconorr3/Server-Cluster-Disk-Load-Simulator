#ifndef NODE_H
#define NODE_H


// Defines the Node class

class Node {
    //makint diskSize, diskUsed;
public:
    Node(int size, int number);
    void diskWrite(int writeSize);
    void run() {
        while (true) {

        }
    };

private:
    int diskSize;
    int diskUsed;
    int nodeNum;
};

#endif