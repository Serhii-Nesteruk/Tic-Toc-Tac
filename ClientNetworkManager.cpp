#include "ClientNetworkManager.h"

#include <iostream>

ClientNetworkManager::~ClientNetworkManager()
{
	closeConnection();
}

bool ClientNetworkManager::init()
{
	if (!winSockInit()) {
		std::cerr << "Failed to initialize a WinSock" << std::endl;
		closeConnection();
		return false;
	}
	else
		std::cerr << "Initialize WinSock is succeeded" << std::endl;

	if (!createClientSocket()) {
		std::cerr << "Failed to crate a client socket" << std::endl;
		closeConnection();
		return false;
	}
	else
		std::cerr << "Client socket is created" << std::endl;
	
	return true;
}

void ClientNetworkManager::setup()
{
	init();
	if (!connectToServer()) {
		std::cerr << "failed connecting to a server" << std::endl;
		closeConnection();
	}
	else
		std::cerr << "Connecting to server is succeeded" << std::endl;

	if (!setNonBlockingMode()) {
		std::cerr << "Failed to set non-blocking mode" << std::endl;
		closeConnection();
	}
	else
		std::cerr << "set non-blocking mode is succeeded" << std::endl;
}

void ClientNetworkManager::closeConnection()
{
	WSACleanup();
	closesocket(clientSocket);
}

bool ClientNetworkManager::setNonBlockingMode()
{
	mode = 1;
	return ioctlsocket(clientSocket, FIONBIO, &mode) == 0;
}

int ClientNetworkManager::receivedBlockId()
{
	int buffer = 0;
	if (::recv(clientSocket, reinterpret_cast<char*>(&buffer), sizeof(buffer), 0) < 0) {
		//std::cerr << "No responce received" << std::endl;
		//closeConnection();
	}
	else
		std::cerr << buffer << std::endl;
	return buffer;
}

bool ClientNetworkManager::sendBlockId(const Block& block)
{
	int blockId = block.getBlockID();
	return ::send(clientSocket, reinterpret_cast<const char*>(&blockId), sizeof(blockId), 0) == 0;
}

bool ClientNetworkManager::winSockInit()
{
	WSADATA ws;
	return WSAStartup(MAKEWORD(2, 2), &ws) == 0;
}

bool ClientNetworkManager::connectToServer()
{
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8808);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	return connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == 0;
}

bool ClientNetworkManager::createClientSocket()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	return clientSocket != INVALID_SOCKET;
}
