#include "ServerNetworkManager.h"

#include <iostream>

ServerNetworkManager::~ServerNetworkManager()
{
	closeConnection();
}

bool ServerNetworkManager::init()
{
	if (!winSockInit()) {
		std::cerr << "Faled to initialize WinSock" << std::endl;
		closeConnection();
		return false;
	}
	else 
		std::cerr << "Initialize WinSock is succeeded" << std::endl;

	if (!createServerSocket()) {
		std::cerr << "Failed to create a server socket" << std::endl;
		closeConnection();
		return false;
	}
	else 
		std::cerr << "Server socket is created" << std::endl;

	if (!createServerAddress()) {
		std::cerr << "Bind failed" << std::endl;
		closeConnection();
		return false;
	}
	else
		std::cerr << "Binding succeeded" << std::endl;

	if (!listening()) {
		std::cerr << "Listening failed";
		closeConnection();
		return false;
	}
	else
		std::cerr << "server is listening" << std::endl;

	if (!createClientSocket()) {
		std::cerr << "Failed to create a client socket" << std::endl;
		closeConnection();
		return false;
	}
	else
		std::cerr << "Client socket is created" << std::endl;

	return true;
}

void ServerNetworkManager::setup()
{
	init();
	if (!setNonBlockingMode()) {
		std::cerr << "Failed to set non-blocking mode" << std::endl;
		closeConnection();
	}
	else
		std::cerr << "set non-blocking mode is succeeded" << std::endl;
}

bool ServerNetworkManager::listening()
{
	return listen(serverSocket, maxClientsNumber) == 0;
}

bool ServerNetworkManager::setNonBlockingMode()
{
	mode = 1;
	return ioctlsocket(serverSocket, FIONBIO, &mode) == 0 &&
		ioctlsocket(clientSocket, FIONBIO, &mode) == 0;
}

bool ServerNetworkManager::sendBlockID(const Block& block)
{
	int blockId = block.getBlockID();
	return ::send(clientSocket, reinterpret_cast<const char*>(&blockId), sizeof(blockId), 0) == 0;
}

int ServerNetworkManager::receivedBlockId()
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

bool ServerNetworkManager::winSockInit()
{
	WSADATA ws;
	return WSAStartup(MAKEWORD(2, 2), &ws) == 0;
}

bool ServerNetworkManager::createServerSocket()
{
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	return serverSocket != INVALID_SOCKET;
}

bool ServerNetworkManager::createServerAddress()
{
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8808);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	return bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == 0;
}

bool ServerNetworkManager::createClientSocket()
{
	clientSocket = accept(serverSocket, NULL, NULL);
	return clientSocket != INVALID_SOCKET;
}

void ServerNetworkManager::closeConnection()
{
	WSACleanup();
	closesocket(serverSocket);
	closesocket(clientSocket);
}
