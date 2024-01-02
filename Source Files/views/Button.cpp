#include <iostream>
#include "../../Header Files/views/Button.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

Button::Button(std::string text, int buttonPosX, int buttonPosY, float buttonWidth, float buttonHeight,
               sf::Color color, sf::RenderWindow &window, sf::Font font)
        : buttonPosX(buttonPosX), buttonPosY(buttonPosY), buttonWidth(buttonWidth),
          buttonHeight(buttonHeight), color(color), window(window), font(font) {

    this->text.setString(text);
}

Button::Button(std::string text, int buttonPosX, int buttonPosY,
               sf::Color color, sf::RenderWindow &window, sf::Font font)
        : buttonPosX(buttonPosX), buttonPosY(buttonPosY), buttonWidth(buttonWidth),
          buttonHeight(buttonHeight), color(color), window(window), font(font) {

    this->buttonWidth = 200;
    this->buttonHeight = 60;

    this->text.setString(text);
}

Button::~Button() {

}

void Button::render(sf::RenderWindow& window) {

    sf::RectangleShape buttonShape(sf::Vector2f(this->buttonWidth, this->buttonHeight));
    buttonShape.setPosition(buttonPosX, buttonPosY);
    buttonShape.setFillColor(color);

    window.draw(buttonShape);

    text.setPosition(buttonPosX + 10, buttonPosY + 7);
    text.setFillColor(sf::Color(0,0,0));
    text.setCharacterSize(30);
    text.setFont(font);

    window.draw(text);
}
