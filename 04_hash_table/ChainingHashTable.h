#ifndef CHAINING_H
#define CHAINING_H

#include "HashTable.h"
#include "Hash.h"
#include <string>
#include <vector>

// Linear probing hash table class
// TODO: modify the class to use public inheritance from the base class HashTable
// Note that you'll need to specify the key and value types to instantiate the template
class ChainingHashTable : public HashTable<std::string, int> {
private:
    // TODO: create the table data member, should be a list of Cell objects (defined in HashTable.h)
    // You may create a pointer and use a dynamic array or vector
    // For the dynamic array, manage new and delete with the constructors and destructors
    // For the vector, be sure to set the size to capacity in the constructor so you can direct index
    vector<vector<Cell<std::string, int> > > table;

public: 
    // TODO: add the constructors & destructors as specified
    ChainingHashTable() {}
    ChainingHashTable(int cap) {
        capacity = cap;
        // vector<vector<Cell<std::string, int> > > table(capacity); // use vector for chaining
        table.resize(capacity);
    }
    ~ChainingHashTable() {table.clear();}

    // TODO: include declarations to override the pure virtual functions from the base class
    unsigned int hash(std::string key);
    void insert(std::string key, int val);
    int remove(std::string key);
    int get(std::string key);
    void printAll(std::string filename);

};

#endif