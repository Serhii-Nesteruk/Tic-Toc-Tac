#include "Game.h"

Game::Game(const sf::Vector2f& windowSize, const std::string& windowName,
    const std::string& blockText, bool isServer, const std::string& serverAddress,
    int serverPort)
    : windowSize(windowSize), windowName(windowName), blockText(blockText),
    isServer(isServer), serverAddress(serverAddress), serverPort(serverPort){
    initWindow();
    initFont();
    initBlocks();
    initNetwork();
}

void Game::eventHandling() {
    sf::Event event;
    while (window.pollEvent(event)) 
        if (event.type == sf::Event::Closed) 
            window.close();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        handleMouseClicked();
    }
}

void Game::display() {
    window.clear();

    drawBlocks();

    window.display();
}

void Game::initWindow() {
    window.create(sf::VideoMode(windowSize.x, windowSize.y), windowName);
}

void Game::initFont()
{
    if (!font.loadFromFile("Roboto-Black.ttf"))
        throw std::exception("Error to load a font");
}

void Game::initBlocks()
{
    const int numRows = 3;
    const int numCols = 3;
    const sf::Color blockColor = sf::Color::Blue;

    for (int i = 0; i < numRows; ++i) {
        int blockId = 0;

        for (int j = 0; j < numCols; ++j) {
            sf::Vector2f position(j * 200, i * 200);
            Block block(position, blockColor, font, blockId);
            blocks.push_back(block);
            ++blockId;
        }
    }
}

void Game::initNetwork()
{
    if (isServer) {
        networkManager.startServer(serverPort);
    }
    else {
        networkManager.connectToServer(serverAddress, serverPort);
    }
}

void Game::handleMouseClicked()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    for (auto& block : blocks) {
        sf::FloatRect blockBounds = block.getBounds();
        if (blockBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
            block.setTextColor(sf::Color::White);
            block.setText(blockText);

            int blockId = block.getBlockID();
            networkManager.sendBlockId(blockId);
        }
    }

    if (networkManager.receiveBlockId())
        for (auto& block : blocks) 
            if (block.getBlockID() == networkManager.getReceivedBlockId())
                block.setText("O");
}

void Game::drawBlocks()
{
    for (auto& block : blocks)
        block.draw(window);
}

void Game::start() {
    while (window.isOpen()) {
        eventHandling();
        display();
    }
}
