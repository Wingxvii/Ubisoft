#include "ServerNetwork.h"
ServerNetwork::ServerNetwork()
{
	//start Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	//startup
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0) {
		std::cout << "cant start winsock" << wsOk;
		return;
	}

	//socket connection
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener == INVALID_SOCKET)
	{
		std::cout << "Can't create a socket!" << std::endl;
		exit(0);
	}

	//socket setup
	serverTCP.sin_addr.S_un.S_addr = INADDR_ANY;
	serverTCP.sin_family = AF_INET;
	serverTCP.sin_port = htons(54000);
	bind(listener, (sockaddr*)&serverTCP, sizeof(serverTCP));
	listen(listener, SOMAXCONN);

}

//cleanup
ServerNetwork::~ServerNetwork()
{
	listening = false;
	closesocket(listener);
	WSACleanup();

}

void ServerNetwork::startUpdates()
{

	//connect player 1
		sockaddr_in client;
		int clientSize = sizeof(client);
		p1 = accept(listener, (sockaddr*)&client, &clientSize);
		if (p1 == -1)
		{
			std::cout << "Can't create a socket!" << WSAGetLastError() << std::endl;
			exit(0);
		}
		else {
			std::cout << "Socket Connected" << std::endl;
		}

		//connect player 2
		sockaddr_in client2;
		int clientSize2 = sizeof(client2);
		p2 = accept(listener, (sockaddr*)&client2, &clientSize2);
		if (p1 == -1)
		{
			std::cout << "Can't create a socket!" << WSAGetLastError() << std::endl;
			exit(0);

		}
		else {
			std::cout << "Socket Connected" << std::endl;
		}

		//begin packet relaying
		std::thread p1Listen = std::thread([&]() {
			while (listening) {
				char* buf = new char[6000];
				int length = recv(p1, buf, 6000, 0);
				if (length <= 0)
				{
					std::cout << "Disconnection" << std::endl;
					// Drop the client
					closesocket(p1);
					listening = false;
				}
				else if (length == SOCKET_ERROR) {
					std::cout << "Recieve Error: " << WSAGetLastError() << std::endl;
				}
				else {
					//directly send to other player
					int sendOK = send(p2, buf, 6000, 0);
					if (sendOK == SOCKET_ERROR) {
						std::cout << "Send Error: " << WSAGetLastError() << std::endl;
					}
				}

			}
			});

		p1Listen.detach();
		std::thread p2Listen = std::thread([&]() {
			while (listening) {
				char* buf = new char[6000];
				int length = recv(p2, buf, 6000, 0);
				if (length <= 0)
				{
					std::cout << "Disconnection" << std::endl;
					closesocket(p2);
					listening = false;
				}
				else if (length == SOCKET_ERROR) {
					std::cout << "Recieve Error: " << WSAGetLastError() << std::endl;
				}
				else {
					int sendOK = send(p1, buf, 6000, 0);
					if (sendOK == SOCKET_ERROR) {
						std::cout << "Send Error: " << WSAGetLastError() << std::endl;
					}

				}
			}
			});
		p2Listen.detach();
}