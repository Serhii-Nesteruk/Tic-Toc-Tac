#include "Game.h"

using namespace std;

int main() {
    bool isServer = false;
    const std::string serverAddress = "127.0.0.1";
    int serverPort = 8808;
    Game client(sf::Vector2f(600.f, 600.f), "TIC-TAC-TOC", "O", isServer, serverAddress, serverPort);
    client.start();

    return 0;
}
