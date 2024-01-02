#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ButtonType.hpp"

class Button {
public:

    Button(std::string text, int posX, int posY, sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type);
    Button(std::string text, int posX, int posY, float buttonWidth, float buttonHeight, sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type);

    ~Button();

    ButtonType buttonType;

    sf::Color color;
    float buttonWidth;
    float buttonHeight;
    float buttonPosX;
    float buttonPosY;

    sf::Text text;
    sf::Font font;

    void render(sf::RenderWindow& window);

    void changeColor(sf::Color newColor);

    bool isClicked(int mouseX, int mouseY) const;

    ButtonType getButtonType();

//    Button& operator=(const Button& other);

private:
    sf::RenderWindow& window;

};
