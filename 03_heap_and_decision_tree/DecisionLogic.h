#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::ostream;
using std::endl;
using std::string;
using std::vector;

class Decision {
public:
	// decision information
	string attribute; // attribute being considered
	double threshold; // threshold for determining branch direction

	// outcome at this level
	int majorityAbove; // outcome to guess if this is leaf and value > threshold
	int majorityBelow; // outcome to guess if this is leaf and value <= threshold

	// used in training operations
	double informationGain;
	int majorityOutcome;
	vector<int> instancesAbove;
	vector<int> instancesBelow;

	// constructors
	Decision() {}
	Decision(string a, double t, int ma, int mb, double i, int m, vector<int> ia, vector<int> ib) {
		attribute = a;
		threshold = t;
		majorityAbove = ma;
		majorityBelow = mb;
		informationGain = i;
		majorityOutcome = m;
		instancesAbove = ia;
		instancesBelow = ib;
	}

	// decisions are ranked based on information gain
	bool operator<(const Decision& d) const {
		return (informationGain < d.informationGain);
	}
	// define other comparisons using the existing one for convenience
	bool operator>(const Decision& rhs) { return rhs < *this; }
	bool operator>=(const Decision& rhs) { return !(*this < rhs); }
	bool operator<=(const Decision& rhs) { return !(*this > rhs); }

	// output operator for printing
	friend ostream& operator<<(ostream&, const Decision&);
};

inline ostream& operator<<(ostream& os, const Decision& d) {
	os << d.attribute << "," << d.threshold << std::endl;
	return os;
}

// support functions for decision logic
void readData(string file, vector<string>& all_attributes, vector< vector<double> >& all_data, vector<int>& outcomes, vector<int>& instances);
vector<double> getInstance( vector<string>& all_attributes, vector< vector<double> >& all_data, int index);
Decision getInformationGain(string attribute, vector<double>& data, vector<int>& outcomes, vector<int>& instances);