#include "Game.h"

using namespace std;

int main() {
    bool isServer = true;
    const std::string serverAddress = "127.0.0.1";
    int serverPort = 8808;
    Game server(sf::Vector2f(600.f, 600.f), "TIC-TAC-TOC", "X", isServer, serverAddress, serverPort);
    server.start();

    return 0;
}
