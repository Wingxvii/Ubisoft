#include "ServerNetwork.h"

int main() {

	ServerNetwork net = ServerNetwork();
	net.startUpdates();

	while (true)
	{
		std::string text;
		std::cin >> text;
	}

}

