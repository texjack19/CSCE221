#include "SortLib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

template <typename T>
void SortLib::CountingSort(T arr[], int size) {
    T min = arr[0];
    T max = 0;
    for (int i = 1; i < size; i++) { // find min
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    for (int i = 0; i < size; i++) { // find max
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    T* sortedArr = new int[size]; // make a new array to store sorted values
    T* count = new int[max - min + 1]; // make an array to store "buckets"

    for (int i = 0; i < size; i++) { // store values of the array into buckets
        count[arr[i] - min]++;
    }
    
    for (int i = 1; i < (max - min + 1); i++) { // for each instance of a particular value in the array,
    // store that value into its corresponding bucket
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) { // use the bucket array to fill sortedArr with values from the bucket
        sortedArr[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--; // decrement count array
    }
    for (int i = 0; i < size; i++) { // put values of sortedArr into new array
        arr[i] = sortedArr[i];
    }
}

template void SortLib::CountingSort(int*, int);