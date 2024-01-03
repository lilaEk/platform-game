#pragma once

#include <functional>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class TextInput {

public:
    TextInput(sf::RenderWindow &window, sf::Font &font);

    void update();
    void updateText();

    void draw();

    void setOnEnterCallback(std::function<void(const std::string&)> callback);

private:
    sf::RenderWindow& window;
    sf::Text inputText;
    std::string inputString;
    bool isFocused;
    bool cursorVisible;
    sf::Clock cursorTimer;
    sf::Font &font;
    std::function<void(const std::string&)> onEnterCallback;

};