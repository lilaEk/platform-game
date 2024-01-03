#include "TextInput.hpp"

void updateText();

TextInput::TextInput(sf::RenderWindow &window, sf::Font &font)
: window(window), font(font) {
        inputText.setFont(font);
        inputText.setCharacterSize(30);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(200, 600);
        isFocused = false;
        inputText.setString("aaa");

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
    if (cursorVisible) {
        inputText.setString(inputString + "|");
    } else {
        inputText.setString(inputString);
    }
}

void TextInput::draw() {
    window.draw(inputText);
}

void TextInput::setOnEnterCallback(std::function<void(const std::string&)> callback) {
    onEnterCallback = std::move(callback);
}
