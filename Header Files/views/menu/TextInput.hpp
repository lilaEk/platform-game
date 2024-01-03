#pragma once

#include <functional>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"

class TextInput {

public:
    TextInput(sf::RenderWindow &window, sf::Font &font);

    void update();
    void updateText();

    void updateIsFocused(bool focused);

    void draw();

    std::string getText();

    void handleEvent( sf::Event &event);

private:
    sf::Event event;

    sf::RenderWindow& window;
    sf::Text inputText;
    std::string inputString;
    bool isFocused;
    bool cursorVisible;
    sf::Clock cursorTimer;
    sf::Font &font;
};