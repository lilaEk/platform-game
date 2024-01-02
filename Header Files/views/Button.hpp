#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class Button {
public:

    Button();
    Button(std::string text, int posX, int posY, sf::Color color, sf::RenderWindow &window, sf::Font font);
    Button(std::string text, int posX, int posY, float buttonWidth, float buttonHeight, sf::Color color, sf::RenderWindow &window, sf::Font font);

    ~Button();

    sf::Color color;
    float buttonWidth;
    float buttonHeight;
    float buttonPosX;
    float buttonPosY;

    sf::Text text;
    sf::Font font;

    void render(sf::RenderWindow& window);

    void changeColor(sf::Color newColor);

//    Button& operator=(const Button& other);

private:
    sf::RenderWindow& window;

};
