#include "Block.h"

Block::Block(sf::Vector2f position, sf::Color color, sf::Font& font, int blockId) 
    : textString(std::string()), textColor(sf::Color::White), blockId(blockId) {
    rectangle.setSize(sf::Vector2f(200, 200));
    rectangle.setPosition(position);
    rectangle.setFillColor(color);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Black);

    text.setFont(font);
    text.setCharacterSize(190);
    text.setFillColor(sf::Color::White);
    text.setString("");
    text.setPosition(position + sf::Vector2f(rectangle.getGlobalBounds().width - 165, rectangle.getGlobalBounds().height - 220));
}

std::string Block::getText() const {
    return textString;
}

void Block::setText(const std::string& newText) {
    textString = newText;
    text.setString(newText);
}

void Block::setTextColor(sf::Color color) {
    textColor = color;
    text.setFillColor(color);
}

void Block::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
    text.setString(textString);
    text.setFillColor(textColor);
    window.draw(text);
}

sf::FloatRect Block::getBounds() const {
    return rectangle.getGlobalBounds();
}
