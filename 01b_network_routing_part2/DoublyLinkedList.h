// TODO: Define the DoublyLinkedList class
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
template <typename T>
class DoublyLinkedList
{
    private:
      Node<T>* head;   // List head pointer
      Node<T>* tail;   // List tail pointer
      int length;   // Stored length of LinkedList

    public:
      // Constructor
      DoublyLinkedList<T>();

      // Linked List operations
      int getLength() {return length;}
      Node<T>* getFront() {return head;}
      Node<T>* getBack() {return tail;}
      void insert(T data, int index);
      T remove(int index);
      void deleteList();
      std::string toString();


      // Rule of three functions
      // Destructor
      ~DoublyLinkedList();
      // Copy constructor
      DoublyLinkedList(const DoublyLinkedList<T>& other);
      // Copy assignment
      DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
};

#endif