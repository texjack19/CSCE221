#include "NetworkRouter.h"
#include <string>
#include <iostream>
#include <sstream>

// receiveRequests:
//   - "receives" network requests by reading from the standard input
void NetworkRouter::receiveRequests(std::istream &is) {
	std::string line; // get one line at a time
	std::stringstream ss; // setup stringstream as an easy way to parse a line
	std::string src, dst, cks, dat;
	// as long as new data is being received, do:
	while (getline(is,line)) {
		ss << line; // put the entire line into a string stream
		// use the space separations to get the first few packet values
		getline(ss, src, ' ');
		getline(ss, dst, ' ');
		getline(ss, cks, ' ');
		getline(ss, dat); // whatever remains is data
		received_requests.push_back(NetworkPacket(src,dst,cks,dat)); // queue the request
		ss.clear();
	}
}

// processRequests:
//   - function checks received requests and determines if internal or external traffic
void NetworkRouter::processRequests() {
	NetworkPacket req;
	// process all received requests
	while (!received_requests.empty()) {
		req = received_requests.pop_front(); // Question: What does this do?
		if (req.destination.compare(0,4,"10.0") == 0) { // Internal traffic starts with 10.0
			internal_requests.push_back(req);
		} else { // Everything else is external and will be sent to another node
			external_requests.push_back(req);
		}
	}
}

// sendRequests:
//   - member function to "send" requests to standard output
void NetworkRouter::sendRequests(std::ostream &os) {
	// "send" internal ones first
	os << "Internal Requests:\n";
	while (!internal_requests.empty()) {
		os << internal_requests.pop_front();
	}
	// "send" external ones
	os << "\nExternal Requests:\n";
	while (!external_requests.empty()) {
		os << external_requests.pop_front();
	}
}