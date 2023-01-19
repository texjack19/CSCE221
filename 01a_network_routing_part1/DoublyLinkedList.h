// TODO: Define the DoublyLinkedList class
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"

class DoublyLinkedList
{
    private:
      Node* head;   // List head pointer
      Node* tail;   // List tail pointer
      int length;   // Stored length of LinkedList

    public:
      // Constructor
      DoublyLinkedList();

      // Linked List operations
      int getLength() {return length;}
      Node* getFront() {return head;}
      Node* getBack() {return tail;}
      void insert(NetworkPacket data, int index);
      NetworkPacket remove(int index);
      void deleteList();
      std::string toString();


      // Rule of three functions
      // Destructor
      ~DoublyLinkedList();
      // Copy constructor
      DoublyLinkedList(const DoublyLinkedList& other);
      // Copy assignment
      DoublyLinkedList& operator=(const DoublyLinkedList& other);
};

#endif