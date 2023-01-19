#ifndef NETWORKPACKET_H
#define NETWORKPACKET_H
#include <string>
#include <iostream>

// Simplified Network Packet has only:
//   - source and destination computer addresses (IPv4)
//   - checksum
//   - data
class NetworkPacket {
// All members and functions are public and implemented in this file
public:
	// For simplicity, we use "string" to store everything
	// In truth, this would all be binary data (e.g., IPv4 addresses like 'source' are 4 bytes)
	std::string source;
	std::string destination;
	std::string checksum;
	std::string data;

	// Default constructor does nothing, must be defined to have the parameterized one below
	NetworkPacket() {}
	// Parameterized constructor puts all info into the packet object
	NetworkPacket(std::string src, std::string dst, std::string cks, std::string dat) {
		source = src;
		destination = dst;
		checksum = cks;
		data = dat;
	}

	// Example of operator overloading, utilizes checksum to confirm a match
	bool operator==(const NetworkPacket& rhs) const {
		return (checksum == rhs.checksum);
	}

	// Provide a print operator to load the packet into an output buffer
	// Question: Why is this defined outside the class rather than as a member function?
	friend std::ostream& operator<<(std::ostream& os, const NetworkPacket& p);
};

// Prints the packet into the passed output stream
// Question: Why is this inline?
inline std::ostream& operator<<(std::ostream& os, const NetworkPacket& p) {
	os << "SRC: " << p.source << ", DST: " << p.destination 
		<< ", CKS: " << p.checksum << ", Data: " << p.data 
		<< std::endl;
	return os;
}


#endif