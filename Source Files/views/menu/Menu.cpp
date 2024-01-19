#include "../../../Header Files/views/menu/Menu.hpp"
#include "../../../Header Files/Game.hpp"

Menu::Menu(MapManager &mapManager, Player *player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window), playerNick(window, font) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }

    init();
}

void Menu::init(){
    initButtons();
    selectedButton = ButtonType::none;
    isStartClickable = false;
}

void Menu::initButtons() {
    Button newGame = Button("new game", 470, 110, upButtonsColor, window, font,ButtonType::new_game);
    Button loadGame = Button("load game", 700, 110, upButtonsColor, window, font,ButtonType::load_game);
    Button highScores = Button("high scores", 470, 200, downButtonsColor, window, font,ButtonType::high_scores);
    Button rules = Button("rules", 700, 200, downButtonsColor, window, font, ButtonType::rules);
    Button yourCharacter = Button("choose your\ncharacter", Game::width / 2 - 100, Game::height / 2 + 20,
                                  200, 120, sf::Color(213, 232, 236), window, font,
                                  ButtonType::choose_your_character);
    Button start = Button("start", 700, 450, sf::Color(151, 164, 166), window, font, ButtonType::start);

    textButtons.push_back(newGame);
    textButtons.push_back(loadGame);
    textButtons.push_back(highScores);
    textButtons.push_back(rules);
    textButtons.push_back(yourCharacter);
    textButtons.push_back(start);

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("../assets/other_elements/arrow.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    Button arrow = Button(buttonTexture, Game::width / 2 + 110, Game::height / 2 + 20, window,
                          ButtonType::choose_your_character);
    picButtons.push_back(arrow);
}

void Menu::update(float deltaTime) {
    updatePlayer(deltaTime);
    updateMenuButtons();
}

void Menu::updatePlayer(float d) {
    player->update(d, false);
}

void Menu::render() {
    renderMap();
    renderPlayer();
    renderButtons();
    renderHeadline();
    renderTextInput();
}

void Menu::renderHeadline() {

    headline.setString(headlineText);
    headline.setPosition(40, 30);
    headline.setFillColor(sf::Color(0, 0, 0));
    headline.setCharacterSize(40);
    headline.setFont(font);

    window.draw(headline);
}

void Menu::renderPlayer() {
    player->render(window);
}

void Menu::renderMap() {
    mapManager.render(window);
}

void Menu::renderButtons() {
    for (Button b: textButtons) {
        b.renderTextButtons(window);
    }
    for (Button b: picButtons) {
        b.renderPicButtons(window);
    }
}

void Menu::renderTextInput() {
    if (selectedButton == ButtonType::new_game ||
        (lastButton == ButtonType::new_game && selectedButton == ButtonType::start)) {
        playerNick.draw();
    }
}

void Menu::updateMenuButtons() {
    switch (selectedButton) {
        case ButtonType::new_game: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }
            textButtons[0].changeColor(buttonChosenColor);

            playerNick.updateIsFocused(true);

            if (playerNick.getText().empty()) {
                isStartClickable = false;
                textButtons[5].changeColor(sf::Color(151, 164, 166));
            } else {
                isStartClickable = true;
                textButtons[5].changeColor(buttonChosenColor);
            }
            break;
        }
        case ButtonType::load_game: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }
            textButtons[1].changeColor(buttonChosenColor);

            setLoadGameSideBlock(window);
            break;
        }
        case ButtonType::high_scores: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }
            textButtons[2].changeColor(buttonChosenColor);

            setRankingSideBlock(window);
            break;
        }
        case ButtonType::rules: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }
            textButtons[3].changeColor(buttonChosenColor);

            setRulesSideBlock(window, font);
            break;
        }
        case ButtonType::choose_your_character: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }

            delete player;
            playerIndex++;
            if (playerIndex == 3) { playerIndex = 0; }
            player = new Player(playersTypeArray[playerIndex]);

            selectedButton = ButtonType::none;
        }
        case ButtonType::start: {

            if (isStartClickable == true) {
                playerNick.updateIsFocused(true);
                lastButton=ButtonType::none;
                handleStartButtonPress();
                selectedButton = ButtonType::none;
                resetNotUsingButtons();
            }

            if (lastButton == ButtonType::new_game) {
                resetNotUsingButtons();
                textButtons[0].changeColor(buttonChosenColor);
            } else if (lastButton == ButtonType::load_game) {
                setLoadGameSideBlock(window);
            } else if (lastButton == ButtonType::rules) {
                setRulesSideBlock(window, font);
            } else if (lastButton == ButtonType::high_scores) {
                setRankingSideBlock(window);
            }
            break;
        }
        default:
            break;
    }

}

void Menu::resetNotUsingButtons() {
    textButtons[0].changeColor(upButtonsColor);
    textButtons[1].changeColor(upButtonsColor);
    textButtons[2].changeColor(downButtonsColor);
    textButtons[3].changeColor(downButtonsColor);
    textButtons[5].changeColor(sf::Color(151, 164, 166));

    isStartClickable = false;
    playerNick.updateIsFocused(false);
}

void Menu::handleButtonClick(int mouseX, int mouseY) {
    if (picButtons[0].isClicked(mouseX, mouseY)) {
        selectedButton = picButtons[0].getButtonType();
        return;
    }
    for (Button &button: textButtons) {
        if (button.isClicked(mouseX, mouseY)) {
            selectedButton = button.getButtonType();
            break;
        }
    }
}

void Menu::setRulesSideBlock(RenderWindow &window, Font font) {
    sf::RectangleShape rulesSideBlock(sf::Vector2f(250, 370));
    rulesSideBlock.setPosition(40, 110);
    rulesSideBlock.setFillColor(sideBlockColor);
    window.draw(rulesSideBlock);

    sf::Text rulesHeadline;
    rulesHeadline.setString("rules");
    rulesHeadline.setPosition(60, 130);
    rulesHeadline.setFillColor(sf::Color(0, 0, 0));
    rulesHeadline.setCharacterSize(40);
    rulesHeadline.setFont(font);
    window.draw(rulesHeadline);

    sf::Text rules;
    rules.setString("a - left movement\n"
                    "d - right movement\n"
                    "w - jump\n"
                    "s - squat\n"
                    "k - puncjh\n"
                    "l - throw attack");
    rules.setPosition(60, 200);
    rules.setFillColor(sf::Color(0, 0, 0));
    rules.setCharacterSize(20);
    rules.setFont(font);
    window.draw(rules);
}

void Menu::setRankingSideBlock(RenderWindow &window) {
    sf::RectangleShape highScoresSideBlock(sf::Vector2f(250, 370));
    highScoresSideBlock.setPosition(40, 110);
    highScoresSideBlock.setFillColor(sideBlockColor);
    window.draw(highScoresSideBlock);
}

void Menu::setLoadGameSideBlock(RenderWindow &window) {
    sf::RectangleShape loadGameSideBlock(sf::Vector2f(250, 370));
    loadGameSideBlock.setPosition(40, 110);
    loadGameSideBlock.setFillColor(sideBlockColor);
    window.draw(loadGameSideBlock);
}

void Menu::handleTextEntered(sf::Event &event) {
    if (selectedButton == ButtonType::new_game) {
        playerNick.handleEvent(event);
    }
}

void Menu::setStartButtonCallback(ButtonCallback callback) {
    startButtonCallback = std::move(callback);
}

void Menu::handleStartButtonPress() {
    if (startButtonCallback) {
        startButtonCallback();
    }
}
