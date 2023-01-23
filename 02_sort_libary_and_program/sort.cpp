#include "lib/SortLib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;
using namespace SortLib;

int main(int argc, char* argv[]) {

	if (argc < 3) { // must have at least 3 arguments for ./sort -a <algorithm>
		std::cerr << "Usage: " << argv[0] << " -a <algorithm> [-i <infile> -o <outfile> -t]" << std::endl;
        return 1;
	}

	// Parse the arguments
	// You can assume if -a is present, so is the algorithm
	// And if -i is present, so is the filename, and so on

	// objects to store values
	string algo = "";
	string input = "";
	string output = "";
	char flag = ' ';
	bool time = false;	

	for (int i = 1; i < argc; i++) {
		if (i % 2 != 0) {
			flag = argv[i][1];
		}
		else {
			if (flag == 'a') { // take in name of algorithm
				algo = argv[i];
			}
			else if (flag == 'i') { // take in name of input file
				input = argv[i];
			}
			else if (flag == 'o') { // take in name of output file
				output = argv[i];
			}
		}	
	}
	if (argv[argc-1][1] == 't') { // if user wants to take time, set time = true
		time = true;
	}

	// Read the input data
	// If a file was provided with -i, read from the file
	// Else, read from stdin (cin)

	std::ifstream ifs(input);
	int size = 0;
	if (input != "") {
		if (!ifs.is_open()) {
			cerr << "Unable to open input file.";
			return 1;
		}
		else {
			ifs >> size;
		}
	}
	else {
		cin >> size;
	}

	int *arr = new int[size]; // dynamic array to store values

	if (input != "") {
		for (int i = 0; i < size; i++) {
			ifs >> arr[i];
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			cin >> arr[i];
		}
	}

	// Set up your timer
	// You can use the included "chrono" library from C++11!
	// Hint: The following line of code would give you the current time

	auto start = std::chrono::high_resolution_clock::now();

	// Apply the sorting algorithm based on the given argument
	if (algo == "bubble") {
		BubbleSort(arr, size);
	}
	else if (algo == "counting") {
		CountingSort(arr, size);
	}
	else if (algo == "quick") {
		QuickSort(arr, size);
	}
	else {
		cerr << "Unsupported sorting algorithm.";
		return 1;
	}
	
	// Stop your timer and find the difference
	// Hint: The following line can compute the difference of two times in microseconds
	// auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// Write the output data
	// If a file was provided with -o, write to that file
	// Else, write to stdout (cout)

	std::ofstream ofs(output);
	if (output != "") { // if ofs has value, write to output file
		if (!ofs.is_open()) {
			cerr << "Could not open output file.";
			return 1;
		}
		for (int i = 0; i < size-1; i++) {
			ofs << arr[i] << " ";
		}
		ofs << arr[size-1] << endl;
	}
	else { // else, write to cout
		for (int i = 0; i < size-1; i++) {
			cout << arr[i] << " ";
		}
		cout << arr[size-1] << endl;
	}

	// If -t was set, print the elapsed time as "Elapsed Time: <duration>"
	if (time == true) {
		cout << "Elapsed Time: " << duration.count() << endl;
	}

	// Cleanup; remember to delete your dynamic data array!
	delete[] arr;

	return 0;
}