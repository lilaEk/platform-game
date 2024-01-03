#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ButtonType.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Button {
public:

    Button(std::string text, int posX, int posY, sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type);
    Button(std::string text, int posX, int posY, float buttonWidth, float buttonHeight, sf::Color color, sf::RenderWindow &window, sf::Font font, ButtonType type);
    Button(const sf::Texture& texture, int posX, int posY, sf::RenderWindow &window, ButtonType type);

    ~Button();

    ButtonType buttonType;

    sf::Color color;
    float buttonWidth;
    float buttonHeight;
    float buttonPosX;
    float buttonPosY;

    sf::Text text;
    sf::Font font;

    void renderTextButtons(sf::RenderWindow& window);
    void renderPicButtons(sf::RenderWindow& window);

    void changeColor(sf::Color newColor);

    bool isClicked(int mouseX, int mouseY) const;

    ButtonType getButtonType();

    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect hitbox;

private:
    sf::RenderWindow& window;

};
