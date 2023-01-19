#include <iostream>
#include "NetworkRouter.h"

int main() {
	NetworkRouter net;

	net.loadBlockedAddresses("blocked.txt");
	net.receiveRequests(std::cin);
	net.processRequests();
	net.sendRequests(std::cout);

	return 0;
}