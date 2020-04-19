#include "stdafx.h"
#include "Network.h"

Network::Network()
{
}

Network::Network(std::string ip)
{	
	//Start Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	//startup
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0) {
		return;
	}

	//socket connection
	tcp = socket(AF_INET, SOCK_STREAM, 0);

	//socket setup
	serverTCP.sin_family = AF_INET;
	serverTCP.sin_port = htons(54000);

	Connect(ip);

}

//connect to server
void Network::Connect(std::string ip)
{
	inet_pton(AF_INET, ip.c_str(), &serverTCP.sin_addr);

	int connResult = connect(tcp, (sockaddr*)&serverTCP, sizeof(serverTCP));
	if (connResult == SOCKET_ERROR) {
		int x = WSAGetLastError();
	}
	else {
		listening = true;
	}
}

//begin multithreaded updates
void Network::StartUpdate()
{
	std::thread update = std::thread([&]() {
		while (listening) {

			char* buf = new char[MAX_PACKET_SIZE];

			int length = recv(tcp, buf, MAX_PACKET_SIZE, 0);
			if (length == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
			}


			Packet packet;
			packet.deserialize(buf);
			packetsIn.push_back(packet);
		}
	
	});
	update.detach();
}

//send data to network
void Network::SendData(int packetType)
{
	Packet packet;
	packet.packet_type = packetType;

	const unsigned int packet_size = sizeof(packet);
	char packet_data[packet_size];

	//seralize
	packet.serialize(packet_data);

	int sendResult = send(tcp, packet_data, packet_size, 0);
}

//cleanup
void Network::ShutDown()
{

	listening = false;
	closesocket(tcp);
	WSACleanup();

}
