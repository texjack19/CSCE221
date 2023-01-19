#ifndef NODE_H
#define NODE_H
#include "NetworkPacket.h"

// TODO: Define the Node class
// Note: Since the functions are all small, you can put everything in this file
// Declare a structure for the node
struct Node {
    NetworkPacket packet;    // The value in this node
    Node* next;  // To point to the next node
    Node* prev; // To point to the previous node

Node():next(nullptr), prev(nullptr), packet(NetworkPacket()) {} // default constructor

Node (const NetworkPacket& d) { // copy constructor
    packet = NetworkPacket(d.source, d.destination, d.checksum, d.data);
    next = nullptr;
    prev = nullptr;
}

NetworkPacket getData() { // returns NetworkPacket
    return packet;
}

Node* getNext() { // returns next Node
    return next;
}

Node* getPrev() { // returns prev Node
    return prev;
}

void setData(const NetworkPacket& d) { // changes data in Node to d
    packet = d;
}

void setNext(Node* n) { // changes next pointer to n
    next = n;
}

void setPrev(Node* p) { // changes prev pointer to p
    prev = p;
}

};

#endif