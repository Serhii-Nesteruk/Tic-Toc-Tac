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

    int blockId = 0;
    for (int i = 0; i < numRows; ++i) 
        for (int j = 0; j < numCols; ++j) {
            sf::Vector2f position(j * 200, i * 200);
            Block block(position, blockColor, font, blockId);
            blocks.push_back(block);
            std::cout << blockId << std::endl;
            ++blockId;
            
        }
}

void Game::initNetwork()
{
    if (isServer) {
        serverNetworkManager.setup();
    }
    else {
        clientNetworkManager.setup();
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

            if (isServer) {
                serverNetworkManager.sendBlockID(block);
            }
            else {
                clientNetworkManager.sendBlockId(block);
            }
        }
    }
}

void Game::drawBlocks()
{
    for (auto& block : blocks)
        block.draw(window);
}

void Game::handleReceived()
{
    int serverBuffer = serverNetworkManager.receivedBlockId();
    int clientBuffer = clientNetworkManager.receivedBlockId();

    for (auto& block : blocks) {
        if (block.getBlockID() == serverBuffer) 
            block.setText(clientSymbol);
        if (block.getBlockID() == clientBuffer)
            block.setText(serverSymbol);
    }
}

void Game::start() {
    while (window.isOpen()) {
        eventHandling();
        handleReceived();
        display();
    }
}
