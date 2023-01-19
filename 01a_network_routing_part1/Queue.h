// TODO: Define the Queue class
// Note: You can do everything in this file since the functions can all be very small (hint: use your list funcitons!)
#include <iostream>
#include <sstream>
#include "DoublyLinkedList.h"
class Queue
{
private:
    DoublyLinkedList list;
    unsigned size;

public:
    Queue(): list(), size(0) {}

    bool empty() {
        if (list.getLength() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    // Inserts a new packet at the end of the queue
    void push_back(NetworkPacket data) {
        list.insert(data, list.getLength());
    }

    // Removes the front element from the queue and returns its value
    NetworkPacket pop_front() {
        return list.remove(0);
    }
    // Like toString method in DoublyLinkedList
    std::string toString() {
        return list.toString();
    }

    const DoublyLinkedList getList() const {return list;}
    unsigned getSize() const {return size;}
};