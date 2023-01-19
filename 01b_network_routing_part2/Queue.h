// TODO: Define the Queue class
// Note: You can do everything in this file since the functions can all be very small (hint: use your list funcitons!)
#include <iostream>
#include <sstream>
#include "DoublyLinkedList.h"
template <typename T>
class Queue
{
private:
    DoublyLinkedList<T> list;
    unsigned size;

public:
    bool empty() { // Checks if queue is empty
        if (list.getLength() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    // Inserts a new packet (type T) at the end of the queue
    void push_back(T data) {
        list.insert(data, list.getLength());
    }

    // Removes the front element from the queue and returns its value
    T pop_front() {
        return list.remove(0);
    }
    // Like toString method in DoublyLinkedList
    std::string toString() {
        return list.toString();
    }

    const DoublyLinkedList<T> getList() const {return list;}
    unsigned getSize() const {return size;}
};