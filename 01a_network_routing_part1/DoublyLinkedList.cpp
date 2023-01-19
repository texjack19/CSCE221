// TODO: Write the source functions for the DoublyLinkedList
#include <iostream>   // For cout and nullptr
#include <sstream>
#include "DoublyLinkedList.h"

using std::cout;
using std::endl;

// Constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), length(0)
{
}

// Copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other)
{
    // helper pointer
    // traverse the list
    Node* marker = other.head;

    head = nullptr;
    tail = nullptr;
    int counter = 0;
    //while marker points to a node, traverse the list
    while (marker != nullptr)
    {
        counter++;
        Node* newnode = new Node;
        newnode->setData(marker->getData());
        newnode->next = nullptr;
        newnode->prev = nullptr;

        if (head == nullptr) {
            head = newnode;
            tail = newnode;
        }
        else {
            // Insert newnode as the last node
            tail->next = newnode;
            // Set newnode prev to tail
            newnode->prev = tail;
            // make newnode the last node
            tail = newnode;
        }
        marker = marker->next;
    }
    length = counter;
}


// Copy assignment
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other)
{
    //self-assignment check
    if (this != &other)
    {
        deleteList();
        head = nullptr;
        tail = nullptr;
        int counter = 0;

        Node* marker = other.head;
        while (marker != nullptr)
        {
            counter++;
            Node* newnode = new Node;
            newnode->setData(marker->getData());
            newnode->next = nullptr;
            newnode->prev = nullptr;

            if (head == nullptr)
            {
                head = newnode;
                tail = newnode;
            }
            else
            {
                tail->next = newnode;
                newnode->prev = tail;
                tail = newnode;
            }
            marker = marker->next;
        }
        length = counter;
    }
    return *this;
}

// The insertNode function inserts a node with value copied to its value number
void DoublyLinkedList::insert(NetworkPacket data, int index)
{
    Node* newnode = new Node();   // A new node to store "data" in
    newnode->setData(data);
    newnode->setNext(nullptr);
    newnode->setPrev(nullptr);

    if (index < 0 || index > length) {
        throw std::out_of_range("Index outside of list bounds");
    }

    // If there are no nodes in the list, make newnode the head and tail
    else if (length == 0) {
        head = newnode;
        tail = newnode;
    }

    // If the new node is to be the 1st in the list, insert it before all other
    // nodes
    else if (index == 0) {
        newnode->setNext(head);
        head->prev = newnode;
        head = newnode;
    }

    else if (index == length) // If the new node is to be the last in the list, insert it at the back
    {
        tail->setNext(newnode);
        newnode->setPrev(tail);
        tail = newnode;
    }

    else   //Otherwise, insert after the previous node and before the marker node
    {
        Node* marker = head;  // To traverse the list

        // Skip all nodes whose number is smaller than value.
        for (unsigned int i = 0; i < index; i++) {
            marker = marker->getNext();
        }
        newnode->setNext(marker);
        newnode->setPrev(marker->getPrev());
        marker->getPrev()->setNext(newnode);
        marker->setPrev(newnode);
    }
    length++;
}

/* The deleteNode function searches for a node with value as its number. The
 * node, if found, is deleted from the list and from memory.
 */
NetworkPacket DoublyLinkedList::remove(int index)
{
    Node* marker = head;   // To traverse the list, initialize marker to head of the list

    // If value is not found or list is empty, throw out of range error
    if (length == 0 || index < 0 || index >= length || head == nullptr) {
        throw std::out_of_range("Index outside of list bounds");
    }

    if (length == 1 && index == 0) // If target node is the only node in the list
    {
        head = nullptr;
        tail = nullptr;
    }
    else if (index == 0) {   // If target node is the first node
        head = head->getNext();
        head->setPrev(nullptr);
    }
    else if (index == (length - 1))   // If target node is the last node
    {
        marker = tail;
        tail = tail->getPrev();
        tail->setNext(nullptr);
    }
    else // If target node is in the middle
    {
        // Skip all nodes whose number is not equal to value
        for (unsigned int i = 0; i < index; i++) {
            marker = marker->next;
        }
        marker->getPrev()->setNext(marker->getNext());  // Link the previous node to the node after marker
        marker->getNext()->setPrev(marker->getPrev());
    }
    length--;
    // create separate node with data from node you're removing
    NetworkPacket data = marker->getData();
    delete marker;
    return data;
}

std::string DoublyLinkedList::toString() {
    std::stringstream ss;
    Node* n = head;
    while(n != nullptr) {
        ss << n->getData() << " ";
        n = n->getNext();
    }
    return ss.str();
}

// This function deletes every node in the list.
void DoublyLinkedList::deleteList()
{
    Node* marker = nullptr;
    // While head is not nullptr
    while (head != nullptr)
    {
        // Save head pointer to marker
        marker = head;
        // Position head at the next node.
        head = head->next;
        marker->next = nullptr;
        delete marker;   // Delete the node
    }
    head = nullptr;
    tail = nullptr;
    marker = nullptr;
}

// This function deletes every node in the list.
DoublyLinkedList::~DoublyLinkedList()
{
    deleteList();
}