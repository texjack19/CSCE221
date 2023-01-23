#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> data;

public:
MaxHeap() {}

MaxHeap(vector<T> list) {
    // constructor accepts a vector of generic objects
    // and converts to a valid max-heap via heapify

    data = list;
    heapify();
}

int getParent(int index) const {
    // return the index of the parent node given the current node
    return (index - 1) / 2;
}

int getLeft(int index) const {
    // return the index of the left child node
    return (index * 2) + 1;
}

int getRight(int index) const {
    // return the index of the right child node
    return (index * 2) + 2;
}

bool empty() const {
    // indicades if the heap is empty or not
    return (data.size() == 0);
}

void swap(T& a, T& b) { // function for swapping purposes
    T temp = a;
    a = b;
    b = temp;
}

void printHeap() { // for testing
    for (int i = 0; i < data.size(); i++) {
        cout << data[i] << endl;
    }
}

void upheap(int index) {
    // given index of a node, propagate it up the max heap if the parent is a smaller value
    if (index == 0) {
        return;
    }
    if (data[index] > data[getParent(index)]) {
        swap(data[index], data[getParent(index)]);
        upheap(getParent(index));
    }
}

void downheap(int index) {
    // given index of a node, propagate it down the max heap if a child has a larger value
    // 3 cases: no children, left child, two children
    // left child, greater means no children
    int greater;
    if (getLeft(index) < data.size() - 1) { // if there are two children
        if (data[getLeft(index)] > data[getRight(index)]) {
            greater = getLeft(index);
        }
        else {
            greater = getRight(index);
        }
    }
    else if (getLeft(index) == data.size() - 1) { // if only one child
        greater = getLeft(index);
    }
    else { // if there are no children
        return;
    }
    if (data[getParent(greater)] < data[greater]) { // if greater child is greater than parent, swap
        swap(data[getParent(greater)], data[greater]);
        downheap(greater); // resort heap
    }
}

void heapify() {
    // heapify the current structure to ensure the
    // rules of a heap are maintained; used in conjunction with
    // the parameterized constructor that accepts a vector
    if (empty()) {
        return;
    }
    for (int i = getParent(data.size()-1); i >= 0; i--) {
        downheap(i);
    }
}

void insert(T elem) {
    // insert an element into the heap; used with upheap
    data.push_back(elem);
    upheap(data.size()-1);
}

T removeMax() {
    // remove an element from the heap; returns max element and uses downheap
    T max = data[0]; // store max element from heap
    swap(data[0], data[data.size() - 1]); // swap largest and smallest value
    data.pop_back(); // remove swapped max
    downheap(0); // downheap to re-sort heap
    return max;
}

};

template <typename T>
vector<T> heapsort(vector<T> v) {
    // recieves an unsorted list and returns a reverse-sorted list (largest first)
    MaxHeap<T> heap(v);
    vector<T> sorted;
    for (int i = 0; i < v.size(); i++) {
        sorted.push_back(heap.removeMax());
    }
    return sorted;
}