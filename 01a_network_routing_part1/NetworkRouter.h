#ifndef NETWORKROUTER_H
#define NETWORKROUTER_H
#include "NetworkPacket.h"
#include <string>
#include <iostream>

#include "Queue.h" // Needs your defined Queue to receive and send packets

// Simplified Network Router has:
//   - single input queue to store received requests
//   - output queues for requests to send internally and ones to send externally
//   - member functions to manage the queues and process requests
class NetworkRouter {
private:
	Queue received_requests;
	Queue internal_requests;
	Queue external_requests;

public:
	void receiveRequests(std::istream &is);
	void processRequests();
	void sendRequests(std::ostream &os);
};


#endif