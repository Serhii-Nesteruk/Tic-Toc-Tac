#include "NetworkManager.h"

NetworkManager::NetworkManager() {
    isServerFlag = false;
}

bool NetworkManager::startServer(unsigned short port) {
    if (server.listen(port) == sf::Socket::Done) {
        isServerFlag = true;
        return true;
    }
    return false;
}

bool NetworkManager::connectToServer(const std::string& address, unsigned short port) {
    if (socket.connect(address, port) == sf::Socket::Done) {
        isServerFlag = false;
        return true;
    }
    return false;
}

void NetworkManager::sendBlockId(int blockId) {
    sf::Packet packet;
    packet << blockId;
    socket.send(packet);
}

bool NetworkManager::receiveBlockId() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done) {
        packet >> receivedBlockId;
        return true;
    }
    return false;
}

void NetworkManager::close() {
    if (isServerFlag) {
        server.close();
    }
    else {
        socket.disconnect();
    }
}

bool NetworkManager::isServer() const {
    return isServerFlag;
}

bool NetworkManager::isConnected() const {
    return socket.getRemoteAddress() != sf::IpAddress::None;
}
