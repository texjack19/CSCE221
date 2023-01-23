#ifndef NODE_H
#define NODE_H

// TODO: Define the Node class
// Note: Since the functions are all small, you can put everything in this file
// Declare a structure for the node
template <typename T>
struct Node {
    T packet;    // The value in this node
    Node<T>* next;  // To point to the next node
    Node<T>* prev; // To point to the previous node

Node<T>():next(nullptr), prev(nullptr), packet(T()) {} // default constructor

Node<T> (const T& d) { // copy constructor
    packet = T(d.source, d.destination, d.checksum, d.data);
    next = nullptr;
    prev = nullptr;
}

T getData() { // return NetworkPacket (type T) in Node
    return packet;
}

Node<T>* getNext() { // returns next Node
    return next;
}

Node<T>* getPrev() { // returns prev Node
    return prev;
}

void setData(const T& d) { // sets NetworkPacket in Node to d
    packet = d;
}

void setNext(Node<T>* n) { // sets next Node to n
    next = n;
}

void setPrev(Node<T>* p) { // sets prev Node to p
    prev = p;
}

};

#endif