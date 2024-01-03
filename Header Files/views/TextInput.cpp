#include <iostream>
#include "TextInput.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

TextInput::TextInput(sf::RenderWindow &window, sf::Font &font)
        : window(window), font(font) {

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(200, 600);
    isFocused = false;
    inputText.setString("your nickname");

    cursorTimer.restart();
}

void TextInput::update() {
    if (isFocused && cursorTimer.getElapsedTime().asSeconds() > 0.5) {
        cursorVisible = !cursorVisible;
        cursorTimer.restart();
        inputText.setString(inputString);    }
}

void TextInput::draw() {
    sf::RectangleShape inputBackground(sf::Vector2f(200, 60));
    inputBackground.setPosition(700, 350);
    inputBackground.setFillColor(sf::Color::White);

    window.draw(inputBackground);

    window.draw(inputText);
}

void TextInput::setOnEnterCallback(std::function<void(const std::string &)> callback) {
    onEnterCallback = std::move(callback);
}

std::string TextInput::getText() {
    return this->inputString;
}

void TextInput::handleEvent(sf::Event &event) {
    this->event=event;
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode < 128) {
            inputString += static_cast<char>(event.text.unicode);
            inputText.setString(inputString);
            std::cout << inputString<<std::endl;
        } else if (event.text.unicode == 8 && !inputString.empty()) {
            inputString.pop_back();
            inputText.setString(inputString);
            std::cout << inputString<<std::endl;
        }
    }
}
