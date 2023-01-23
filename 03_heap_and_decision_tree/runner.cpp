#include "DecisionLogic.h"
#include "DTree.h"
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;


int main(int argc, char* argv[]) {

	if (argc < 3) { // must have at least 3 arguments for ./sort -a <algorithm>
		std::cerr << "Usage: " << argv[0] << " <training data> <testing data>" << std::endl;
		return 1;
	}

	// get filenames
	string trainfile = std::string(argv[1]);
	string testfile = std::string(argv[2]);


	// read training data
	vector<string> attributes;
	vector< vector<double> > data;
	vector<int> outcomes;
	vector<int> instances;
	readData(trainfile, attributes, data, outcomes, instances);

	// train the decision tree
	DTree dt;
	dt.train(attributes,data,outcomes,instances);


	// read testing data
	attributes.clear();
	data.clear();
	outcomes.clear();
	instances.clear();
	readData(testfile, attributes, data, outcomes, instances);

	// test all instances by classifying them through the decision tree
	double totalCounted = 0;
	double totalCorrect = 0;
	for (int i = 0; i < instances.size(); i++) {
		vector<double> inst = getInstance(attributes,data,i);
		int outc = dt.classify(attributes,inst);
		if (outc == outcomes.at(i)) {
			totalCorrect++;
		}
		totalCounted++;
	}

	// print tree structure
	std::cout << dt.levelOrderTraversal() << std::endl;
	
	// output accuracy = correct / total
	std::cout << "Accuracy: " << totalCorrect / totalCounted << std::endl;

	return 0;
}