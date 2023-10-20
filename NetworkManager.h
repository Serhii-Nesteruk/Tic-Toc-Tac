#pragma once

#include <SFML/Network.hpp>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager() = default;

    bool startServer(unsigned short port);
    bool connectToServer(const std::string& address, unsigned short port);
    void sendBlockId(int blockId);
    bool receiveBlockId();
    void close();

    bool isServer() const;
    bool isConnected() const;

    inline int getReceivedBlockId() const {
        return receivedBlockId;
    }

private:
    int receivedBlockId = 0;
    sf::TcpListener server;
    sf::TcpSocket socket;
    bool isServerFlag = false;
};
