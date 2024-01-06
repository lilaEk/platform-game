#include <iostream>
#include "../../../Header Files/views/menu/TextInput.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


TextInput::TextInput(sf::RenderWindow &window, sf::Font &font)
        : window(window), font(font) {

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(710, 385);
    isFocused = false;
    inputText.setString("your nickname");

    cursorTimer.restart();
}

void TextInput::update() {
    if (isFocused && cursorTimer.getElapsedTime().asSeconds() > 0.5) {
        cursorVisible = !cursorVisible;
        cursorTimer.restart();
        updateText();
    }
}

void TextInput::updateText() {
    std::string displayedText = inputString;
    if (cursorVisible) {
        displayedText += "_";
    }
    inputText.setString(displayedText);
}

void TextInput::updateIsFocused(bool currentFocused){
    this->isFocused=currentFocused;
}

void TextInput::draw() {
    sf::RectangleShape inputBackground(sf::Vector2f(200, 60));
    inputBackground.setPosition(700, 370);
    inputBackground.setFillColor(sf::Color::White);

    window.draw(inputBackground);

    window.draw(inputText);
}

std::string TextInput::getText() {
    return this->inputString;
}

void TextInput::handleEvent(sf::Event &event) {
    this->event=event;
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode < 128) {
            inputString += static_cast<char>(event.text.unicode);
            updateText();
        } else if (event.text.unicode == 8 && !inputString.empty()) {
            inputString.pop_back();
            updateText();
        }
    }
}
