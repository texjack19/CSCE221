#include "ChainingHashTable.h"
#include <iostream>
#include <fstream>
using namespace std;

unsigned int ChainingHashTable::hash(std::string key) {
    return Hash::PRH24(key) % capacity;
}

void ChainingHashTable::insert(std::string key, int val) {
    // follows behavior of get, but either updates value or adds a new entry
    int hashIndex = hash(key);
    for (int i = 0; i < table[hashIndex].size(); i++) {
        if ((table[hashIndex][i]).key == key) { // if match, update value
            table[hashIndex][i].value = val;
            return;
        }
    }
    Cell<string, int> newCell(key, val);
    table[hashIndex].push_back(newCell);
}

int ChainingHashTable::remove(std::string key) {
    // clear a cell and return the value of the key, if not found, throw runtime_error
    int hashIndex = hash(key);
    for (int i = 0; i < table[hashIndex].size(); i++) {
        if ((table[hashIndex][i]).key == key) { // if match, update value
            int temp = table[hashIndex][i].value;
            table[hashIndex].erase(table[hashIndex].begin() + i);
            return temp;
        }
    }
    throw std::runtime_error("Key not found");
}

int ChainingHashTable::get(std::string key) {
    int hashIndex = hash(key);
    for (int i = 0; i < table[hashIndex].size(); i++) {
        if ((table[hashIndex][i]).key == key) { // if match, update value
            return table[hashIndex][i].value;
        }
    }
    return 0;
}

void ChainingHashTable::printAll(std::string filename) {
    std::ofstream ofs(filename);
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j].key != "") { // print to file if not blank
            ofs << table[i][j].key << " " << table[i][j].value << std::endl;
            }
        }
    }
}