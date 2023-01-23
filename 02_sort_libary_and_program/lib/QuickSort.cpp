#include "SortLib.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <typename T> // takes last element as pivot, places the pivot element at its correct position in sortedarray, 
// places all smaller to left of pivot and all greater elements to right of pivot
int partition(T arr[], int low, int high) {
    T pivot = arr[high]; // pivot is being set at the end
    T temp; // temp value for swapping purposes
    int i = low - 1; // index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j < high; j++) { // sorts if current element is smaller than the pivot
        if (arr[j] <= pivot) {
            i++; // increment index of smaller element
            // swap arr[i] and arr[j]
            temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
        }
    }
    // swap arr[i+1] and arr[high]
    temp = arr[i+1];
	arr[i+1] = arr[high];
	arr[high] = temp;
    return i + 1;
}

template <typename T>
void QuickSortRecursive(T arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high); // retrieve pivot position from partition() function, 
        // pivot being the value in correct position

        QuickSortRecursive(arr, low, pivot - 1); // sort left sublist from the left to the last val before partition

        QuickSortRecursive(arr, pivot + 1, high); // sort right sublist from right of partition to end of list
    }
}

template <typename T>
void SortLib::QuickSort(T arr[], int size) {
    QuickSortRecursive(arr, 0, size - 1); // call recursive quicksort function with 0 and size-1 as index
}

template void SortLib::QuickSort(int*, int);