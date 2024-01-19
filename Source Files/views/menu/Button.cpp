#include <iostream>
#include "../../../Header Files/views/menu/Button.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


Button::Button(std::string text, int buttonPosX, int buttonPosY, float buttonWidth, float buttonHeight,
               sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type)
        : buttonPosX(buttonPosX), buttonPosY(buttonPosY), buttonWidth(buttonWidth),
          buttonHeight(buttonHeight), color(color), window(window), font(font), buttonType(type) {

    this->text.setString(text);
}

Button::Button(std::string text, int buttonPosX, int buttonPosY,
               sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type)
        : buttonPosX(buttonPosX), buttonPosY(buttonPosY), buttonWidth(buttonWidth),
          buttonHeight(buttonHeight), color(color), window(window), font(font), buttonType(type) {

    buttonWidth = 200;
    buttonHeight = 60;

    this->text.setString(text);
}

Button::Button(const sf::Texture &texture, int posX, int posY, sf::RenderWindow &window, ButtonType type)
        : texture(texture), buttonPosX(posX), buttonPosY(posY), window(window), buttonType(type){
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);

    hitbox = sf::IntRect(static_cast<int>(posX), static_cast<int>(posY),
                         static_cast<int>(sprite.getGlobalBounds().width),
                         static_cast<int>(sprite.getGlobalBounds().height));
}

Button::~Button() {}

void Button::renderTextButtons(sf::RenderWindow &window) {

    sf::RectangleShape buttonShape(sf::Vector2f(buttonWidth, buttonHeight));
    buttonShape.setPosition(buttonPosX, buttonPosY);
    buttonShape.setFillColor(color);

    window.draw(buttonShape);

    text.setPosition(buttonPosX + 15, buttonPosY + 10);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setCharacterSize(30);
    text.setFont(font);

    window.draw(text);
}

void Button::renderPicButtons(sf::RenderWindow &window) {

    sprite.setTexture(texture);
    sprite.setPosition(buttonPosX, buttonPosY);

    window.draw(sprite);
}

void Button::changeColor(sf::Color newColor) {
    color = newColor;
}

bool Button::isClicked(int mouseX, int mouseY) const {
    if (mouseX >= buttonPosX && mouseX <= buttonPosX + buttonWidth &&
            mouseY >= buttonPosY && mouseY <= buttonPosY + buttonHeight){
        return true;
    }
    return hitbox.contains(mouseX, mouseY);
}

ButtonType Button::getButtonType() {
    return buttonType;
}

