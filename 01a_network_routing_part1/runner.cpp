#include <iostream>
#include "NetworkRouter.h"

int main() {
	NetworkRouter net;

	net.receiveRequests(std::cin);
	net.processRequests();
	net.sendRequests(std::cout);

	return 0;
}