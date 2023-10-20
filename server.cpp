#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Block {
public:
    Block(sf::Vector2f position, sf::Color color, sf::Font& font) {
        // Ініціалізація решти коду
        rectangle.setSize(sf::Vector2f(200, 200));
        rectangle.setPosition(position);
        rectangle.setFillColor(color);
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color::Black);

        text.setFont(font); // Встановіть шрифт для тексту
        text.setCharacterSize(190);
        text.setFillColor(sf::Color::White);
        text.setString("");
        text.setPosition(position + sf::Vector2f(rectangle.getGlobalBounds().width - 165, rectangle.getGlobalBounds().height - 220));

        // Додайте поля для зберігання тексту та колору
        this->textString = std::string();
        this->textColor = sf::Color::White;
    }

    // Додайте методи для отримання тексту та колору
    std::string getText() const {
        return textString;
    }

    sf::Color getTextColor() const {
        return textColor;
    }

    // Додайте методи для встановлення тексту та колору
    void setText(const std::string& newText) {
        textString = newText;
        text.setString(newText);
    }

    void setTextColor(sf::Color color) {
        textColor = color;
        text.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);

        // Встановлення тексту та кольору тексту
        text.setString(textString);
        text.setFillColor(textColor);
        
        window.draw(text); // Відобразіть текст разом з блоком
    }

    sf::FloatRect getBounds() const {
        return rectangle.getGlobalBounds();
    }

private:
    sf::RectangleShape rectangle;
    sf::Text text;

    // Додайте поля для зберігання тексту та колору
    std::string textString;
    sf::Color textColor;
};


int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "TICTOCTAC");

    sf::Font font;
    if (!font.loadFromFile("Roboto-Black.ttf"))
        return 1;

    const int numRows = 3;
    const int numCols = 3;
    const sf::Color blockColor = sf::Color::Blue;

    std::vector<Block> blocks{};

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            sf::Vector2f position(j * 200, i * 200);
            Block block(position, blockColor, font);
            blocks.emplace_back(block);
        }
    }

    bool isMouseClicked = false; // Флаг для відстеження натискання миші

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && !isMouseClicked) {
                // Обробляйте натискання миші тут
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (auto& block : blocks) {
                    sf::FloatRect blockBounds = block.getBounds();
                    if (blockBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                        block.setTextColor(sf::Color::White);
                        block.setText("X"); // Змініть текст блоку
                    }
                }
                isMouseClicked = true; // Встановіть флаг, що мишка була натиснута
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Забезпечте, щоб текст і колір тексту були встановлені лише один раз
            isMouseClicked = false;
        }

        window.clear();

        for (auto& block : blocks) {
            block.draw(window);
        }

        window.display();
    }


    return 0;
}
