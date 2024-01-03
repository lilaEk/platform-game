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

    void draw();

    void setOnEnterCallback(std::function<void(const std::string&)> callback);

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
    std::function<void(const std::string&)> onEnterCallback;
};