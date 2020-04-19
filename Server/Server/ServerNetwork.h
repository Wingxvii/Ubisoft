#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <thread>
#include <queue>

#pragma comment (lib, "ws2_32.lib")

#pragma once
class ServerNetwork
{
public:
	ServerNetwork();
	~ServerNetwork();

	//UDP Socket
	SOCKET listener;

	SOCKET p1;
	SOCKET p2;

	sockaddr_in serverTCP;

	bool listening = true;

	//begin listening to input signals
	void startUpdates();
};

