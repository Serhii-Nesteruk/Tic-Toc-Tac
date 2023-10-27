#pragma once

#include "Block.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

class ServerNetworkManager final {
public:
	ServerNetworkManager() = default;
	~ServerNetworkManager();

	bool init();
	void setup();
	bool listening();
	bool setNonBlockingMode();
	bool sendBlockID(const Block& block);
	int receivedBlockId();
	void closeConnection();

private:
	bool winSockInit();
	bool createServerSocket();
	bool createServerAddress();
	bool createClientSocket();

	inline static const int maxClientsNumber = 1;
private:
	SOCKET serverSocket;
	SOCKET clientSocket;
	sockaddr_in serverAddress;
	u_long mode = 0;
};