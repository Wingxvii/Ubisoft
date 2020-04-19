#include "ServerNetwork.h"

int main() {

	ServerNetwork net = ServerNetwork();
	net.startUpdates();

	//loop to keep the program going
	while (true)
	{
		std::string text;
		std::cin >> text;
	}

}

