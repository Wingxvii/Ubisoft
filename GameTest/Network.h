#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include "Packet.h"
	 

class Network
{
public:
	Network();
	Network(std::string);

	SOCKET tcp;
	SOCKET client;
	sockaddr_in serverTCP;

	bool listening = false;
	bool host;

	std::vector<Packet> packetsIn;


	//connect to server
	void Connect(std::string ip);

	//accept client
	void AcceptClient();

	//begin multithreaded updates
	void StartUpdate();

	//send data
	void SendData(int packetType);

	//process data
	void ProcessData(Packet pack);

	void ShutDown();
};

