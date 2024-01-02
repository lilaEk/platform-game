#include <iostream>
#include "../../Header Files/views/Button.hpp"
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
          buttonHeight(buttonHeight), color(color), window(window), font(font), buttonType(type){

    this->buttonWidth = 200;
    this->buttonHeight = 60;

    this->text.setString(text);
}

//Button& Button::operator=(const Button& other) {
//    if (this != &other) {
//        this->buttonPosX = other.buttonPosX;
//        this->buttonPosY = other.buttonPosY;
//        this->buttonWidth = other.buttonWidth;
//        this->buttonHeight = other.buttonHeight;
//        this->color = other.color;
////        this->window = other.window;
//        this->font = other.font;
//
//        this->text.setString(other.text.getString());
//        this->text.setPosition(other.text.getPosition());
//        this->text.setFillColor(other.text.getFillColor());
//        this->text.setCharacterSize(other.text.getCharacterSize());
//        this->text.setFont(*other.text.getFont());
//    }
//    return *this;
//}

Button::~Button() { }

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

void Button::changeColor(sf::Color newColor) {
    this->color=newColor;
}

bool Button::isClicked(int mouseX, int mouseY) const {
    return (mouseX >= buttonPosX && mouseX <= buttonPosX + buttonWidth &&
            mouseY >= buttonPosY && mouseY <= buttonPosY + buttonHeight);
}

ButtonType Button::getButtonType() {
    return this->buttonType;
}

