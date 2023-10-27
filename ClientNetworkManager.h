#pragma once

#include "Block.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

class ClientNetworkManager {
public:
	ClientNetworkManager() = default;
	~ClientNetworkManager();

	bool init();
	void setup();
	void closeConnection();
	bool setNonBlockingMode();
	bool sendBlockId(const Block& block);
	int receivedBlockId();
private:
	bool winSockInit();
	bool connectToServer();
	bool createClientSocket();

private:
	SOCKET clientSocket;
	sockaddr_in serverAddress;
	u_long mode = 0;

};