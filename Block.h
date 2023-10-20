#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Block {
public:
    Block(sf::Vector2f position, sf::Color color, sf::Font& font, int blockId);
    ~Block() = default;
    std::string getText() const;
    void setText(const std::string& newText);
    void setTextColor(sf::Color color);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    inline int getBlockID() const {
        return blockId;
    }

private:
    sf::RectangleShape rectangle;
    sf::Text text;
    std::string textString;
    sf::Color textColor;

    int blockId = 0;
};
