#include "DecisionLogic.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;


/*******************
 * READ DATA FILES *
 *******************/

// custom delimiter definition to support splitting on CSV's comma
struct comma_delimiter : std::ctype<char> {
	comma_delimiter() : std::ctype<char>(get_table()) {}
	static mask const* get_table()
	{
		static mask m[table_size];
		m[','] = std::ctype_base::space;
		return m;
	}
};

// read data function maps an csv input file into parallel vectors
void readData(string file, vector<string>& attributes, vector< vector<double> >& data, vector<int>& outcomes, vector<int>& instances) {
	// check that training data can be accessed
	std::ifstream trainin(file);
	if (!trainin.is_open()) {
		std::cerr << "Unable to open training file!" << std::endl;
		return;
	}

	// setup file reading
	string stringline;
	std::stringstream streamline;

	// get labels from first line
	getline(trainin, stringline);
	streamline << stringline;

	string label;
	while (!streamline.eof()) {
		getline(streamline, label, ',');
		attributes.push_back(label);
	}
	streamline.clear();

	// assume the last item is the outcomes
	attributes.pop_back();

	// get data in parallel vectors (managed by a 2D vector structure)
	data.resize(attributes.size()); // set number of parallel vectors -- one for each attribute

	streamline.imbue(std::locale(trainin.getloc(), new comma_delimiter));
	double value;
	int instanceCounter = 0;
	while (!trainin.eof()) {
		getline(trainin, stringline);
		streamline << stringline;
		for (int i = 0; i < attributes.size(); i++) {
			streamline >> value;
			data.at(i).push_back(value);
		}
		// read the outcome last
		int o;
		streamline >> o;
		outcomes.push_back(o);
		// with a matching instance count
		instances.push_back(instanceCounter);
		instanceCounter++;
		streamline.clear();
	}
}

// converts from the attribute-ordered 2D data into a single instance-ordered array of data
vector<double> getInstance( vector<string>& attributes, vector< vector<double> >& data, int index) {
	vector<double> instance;
	for (int i = 0; i < attributes.size(); i++) {
		instance.push_back(data.at(i).at(index));
	}
	return instance;
}


/**********************
 * TRAINING FUNCTIONS *
 **********************/

// before creating a decision point, we explore all possible pre-decisions to get their info gain
struct PreDecision {
	double value;
	vector<int> outcomes0;
	vector<int> outcomes1;
	// implement a simple < comparison to leverage the STL sort
	bool operator<(const PreDecision& pd) const {
		return (value < pd.value);
	}
};

// get information gain for a particular attribute over this set of instances
Decision getInformationGain(string att, vector<double>& dat, vector<int>& out, vector<int>& inst) {
	int countOutcomes0 = 0; // keep track of total outcome counts for later computation
	int countOutcomes1 = 0;
	int totalOutcomes = inst.size();
	vector<PreDecision> pd; // we will explore all possible decisions
	for (int j = 0; j < inst.size(); j++) { // for the instances under consideration
		double val = dat.at(inst.at(j)); // get the possible threshold point
		int outc = out.at(inst.at(j));
		if (outc == 0) {
			countOutcomes0++;
		} else {
			countOutcomes1++;
		}
		bool exists = false;
		for (int k = 0; k < pd.size(); k++) { // determine if this is a new possible decision or existing one
			if (pd.at(k).value == val) { // exists, update the outcome instances
				exists = true;
				if (outc == 0) {
					pd.at(k).outcomes0.push_back(inst.at(j));
				} else {
					pd.at(k).outcomes1.push_back(inst.at(j));
				}
			}
		}
		if (!exists) { // create a new pre-decision point
			PreDecision npd;
			npd.value = val;
			if (outc == 0) {
				npd.outcomes0.push_back(inst.at(j));
			} else {
				npd.outcomes1.push_back(inst.at(j));
			}
			pd.push_back(npd);
		}
	}
	// now go through the possible decision thresholds
	// we must compute the information gained about each outcome for each possible threshold
	// since the threshold is linear, less than or greater, we must sort the pd vector on the value
	std::sort(pd.begin(), pd.end());
	double max01 = 0; // no separability yet
	double max10 = 0;
	int max01ind = 0; // pick endpoints to handle edge cases; should move inward
	int max10ind = pd.size()-1;
	for (int j = 0; j < pd.size(); j++) {
		// get counts of outcomes relative this possible decision point
		int curr0 = pd.at(j).outcomes0.size();
		int curr1 = pd.at(j).outcomes1.size();
		int below0 = curr0;
		int below1 = curr1;
		for (int k = 0; k < j; k++) {
			below0 += pd.at(k).outcomes0.size();
			below1 += pd.at(k).outcomes1.size();
		}
		int above0 = countOutcomes0 - below0;
		int above1 = countOutcomes1 - below1;

		// compute what this tells us relative the total outcomes (a simplified info gain)
		double gain0below = static_cast<double>(below0) / countOutcomes0 - static_cast<double>(below1) / countOutcomes1;
		double gain0above = static_cast<double>(above0) / countOutcomes0 - static_cast<double>(above1) / countOutcomes1;

		// update our tracker for best
		if (max01 < gain0below) {
			max01 = gain0below;
			max01ind = j;
		}
		if (max10 < gain0above) {
			max10 = gain0above;
			max10ind = j;
		}
	}

	// turn the most promising pre-decision into a decision and return
	double overall;
	int overallInd, majBelow, majAbove;
	if (max01 > max10) {
		overall = max01;
		overallInd = max01ind;
		majBelow = 1;
		majAbove = 0;
	} else {
		overall = max10;
		overallInd = max10ind;
		majBelow = 0;
		majAbove = 1;
	}

	Decision d;
	d.attribute = att;
	d.threshold = pd.at(overallInd).value;
	d.informationGain = overall;
	d.majorityAbove = majAbove;
	d.majorityBelow = majBelow;

	if (pd.at(overallInd).outcomes0.size() >= pd.at(overallInd).outcomes1.size()) {
		d.majorityOutcome = 0;
	} else {
		d.majorityOutcome = 1;
	}

	vector<int> belowInst, aboveInst;
	for (int j = 0; j <= overallInd; j++) {
		for (int k = 0; k < pd.at(j).outcomes0.size(); k++) {
			belowInst.push_back(pd.at(j).outcomes0.at(k));
		}
		for (int k = 0; k < pd.at(j).outcomes1.size(); k++) {
			belowInst.push_back(pd.at(j).outcomes1.at(k));
		}
	}
	for (int j = overallInd + 1; j < pd.size(); j++) {
		for (int k = 0; k < pd.at(j).outcomes0.size(); k++) {
			aboveInst.push_back(pd.at(j).outcomes0.at(k));
		}
		for (int k = 0; k < pd.at(j).outcomes1.size(); k++) {
			aboveInst.push_back(pd.at(j).outcomes1.at(k));
		}
	}

	d.instancesAbove = aboveInst;
	d.instancesBelow = belowInst;

	return d;
}

