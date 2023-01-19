#ifndef NETWORKROUTER_H
#define NETWORKROUTER_H
#include "NetworkPacket.h"
#include <string>
#include <iostream>

#include "Queue.h" // Needs your defined Queue to receive and send packets
#include "DoublyLinkedList.h"

// Simplified Network Router has:
//   - single input queue to store received requests
//   - output queues for requests to send internally and ones to send externally
//   - member functions to manage the queues and process requests
//   - extended to support blocked IP addresses with a templated linked list
class NetworkRouter {
private:
	Queue<NetworkPacket> received_requests;
	Queue<NetworkPacket> internal_requests;
	Queue<NetworkPacket> external_requests;

public:
	void receiveRequests(std::istream &is);
	void processRequests();
	void sendRequests(std::ostream &os);
};


#endif