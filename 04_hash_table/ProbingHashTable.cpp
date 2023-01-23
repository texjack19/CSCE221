#include "ProbingHashTable.h"
#include <iostream>
#include <fstream>
using namespace std;

unsigned int ProbingHashTable::hash(std::string key) {
    return Hash::PRH24(key) % capacity;
}

void ProbingHashTable::insert(std::string key, int val) {
    // follows behavior of get, but either updates value or adds a new entry
    int hashIndex = hash(key);
    if ((table[hashIndex]).key == "") { // if blank, insert a new entry
        table[hashIndex].key = key;
        table[hashIndex].value = val;
    }
    else if ((table[hashIndex]).key == key) { // if key matches, update value
        table[hashIndex].value = val;
    }
    else if ((table[hashIndex]).key != key) { // if key exists but does not match, initiate linear probing process
        for (unsigned int i = 1; i < capacity; i++) {
            hashIndex = (i+hashIndex) % capacity;
            if (table[hashIndex].key == key) { // if there is a key match, update value
                table[hashIndex].value = val;
                break;
            }
            if (table[hashIndex].key == "") { // if blank, add new entry
                table[hashIndex].key = key;
                table[hashIndex].value = val;
                break;
            }
        }
    }
}

int ProbingHashTable::remove(std::string key) {
    // clear a cell and return the value of the key, if not found, throw runtime_error
    int hashIndex = hash(key);
    if ((table[hashIndex]).key == "") { // if key doesn't exist, throw runtime_error
        throw std::runtime_error("Key not found");
    }
    if ((table[hashIndex]).key == key) { // if key found, remove and return value
        int temp = table[hashIndex].value;
        table[hashIndex].value = 0;
        table[hashIndex].key = "";
        return temp;
    }
    if ((table[hashIndex]).key != key) {
        for (unsigned int i = 1; i < capacity; i++) {
            hashIndex = (i+hashIndex) % capacity;
            if (table[hashIndex].key == key) {
                int temp = table[hashIndex].value;
                table[hashIndex].value = 0;
                table[hashIndex].key = "";
                return temp;
            }
        }
        throw std::runtime_error("Key not found");
    }
}

int ProbingHashTable::get(std::string key) {
    int hashIndex = hash(key);
    if ((table[hashIndex]).key == "") { // if blank, return 0
        return 0;
    }
    if ((table[hashIndex]).key == key) { // if match, return value
        return (table[hashIndex]).value;
    }
    if ((table[hashIndex]).key != key) { // if no match, initiate linear search
        for (unsigned int i = 1; i < capacity; i++) {
            hashIndex = (i+hashIndex) % capacity;
            if (table[hashIndex].key == key) {
                return table[hashIndex].value;
            }
            if (table[hashIndex].key == "") {break;}
        }
    }
    return 0; 
}

void ProbingHashTable::printAll(std::string filename) {
    std::ofstream ofs(filename);
    for (int i = 0; i < capacity; i++) {
        if (table[i].key != "") { // print to file if not blank
            ofs << table[i].key << " " << table[i].value << std::endl;
        }
    }
}