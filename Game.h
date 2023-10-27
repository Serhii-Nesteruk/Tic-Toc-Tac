#pragma once

#include "Block.h"
#include "ServerNetworkManager.h"
#include "ClientNetworkManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Game {
public:
    Game(const sf::Vector2f& windowSize, const std::string& windowName,
        const std::string& blockText, bool isServer, const std::string& serverAddress,
        int serverPort);
    ~Game() = default;
    void start();

private:
    void eventHandling();
    void display();

    void initWindow();
    void initFont();
    void initBlocks();
    void initNetwork();
    void handleMouseClicked();
    void drawBlocks();

    void handleReceived();

    inline static const std::string clientSymbol = "O";
    inline static const std::string serverSymbol = "X";
private:

    ServerNetworkManager serverNetworkManager;
    ClientNetworkManager clientNetworkManager;
    bool isServer = false;
    std::string serverAddress{};
    int serverPort = 0;

    std::string blockText{};
    sf::Vector2f windowSize;
    std::string windowName{};
    sf::RenderWindow window;
    sf::Font font;
    std::vector<Block> blocks{};
    bool isMouseClicked = false;
};
