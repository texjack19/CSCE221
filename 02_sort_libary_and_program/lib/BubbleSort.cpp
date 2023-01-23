#include "SortLib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

template <typename T>
void SortLib::BubbleSort(T arr[], int size) {
	T temp; // temp value for swapping purposes
	bool swapped;
	for (int i = 0; i < size - 1; i++) { // iterating over the entire list i times
		swapped = false;
		for (int j = 0; j < size - i - 1; j++) { // iterating through list and swapping values
			if (arr[j] > arr[j + 1]) { // swap if value at lesser index is greater
				temp = arr[j];
			    arr[j] = arr[j+1];
				arr[j+1] = temp;
				swapped = true;
			}
		}
		if (swapped == false) { // breaks the loop when the array is fully sorted
			break;
		}
	}
}

template void SortLib::BubbleSort(int*, int);