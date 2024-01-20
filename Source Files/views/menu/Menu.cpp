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

void Menu::update(float deltaTime, const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData) {
    updatePlayer(deltaTime);
    updateMenuButtons(rankingData);
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

void Menu::renderRanking(const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData) {
    drawSideBlockAndHeadline("ranking", window);

    sf::Text nameHeader, pointsHeader;
    nameHeader.setString("Name");
    pointsHeader.setString("Points");

    nameHeader.setPosition(200, 200);
    pointsHeader.setPosition(400, 200);

    nameHeader.setFillColor(sf::Color(0, 0, 0));
    pointsHeader.setFillColor(sf::Color(0, 0, 0));

    nameHeader.setCharacterSize(20);
    pointsHeader.setCharacterSize(20);

    nameHeader.setFont(font);
    pointsHeader.setFont(font);

    window.draw(nameHeader);
    window.draw(pointsHeader);

    for (size_t i = 0; i < 10; ++i) {
        std::string placeText, nameText, pointsText;

        if (i < rankingData.size()) {
            const auto& playerTuple = rankingData[i];
            placeText = std::to_string(i + 1) + ".";
            nameText = std::get<0>(playerTuple);
            pointsText = std::to_string(std::get<3>(playerTuple));
        } else {
            placeText = std::to_string(i + 1) + ".";
            nameText = "empty";
            pointsText = "0";
        }

        sf::Text placeEntry, nameEntry, pointsEntry;

        placeEntry.setString(placeText);
        nameEntry.setString(nameText);
        pointsEntry.setString(pointsText);

        placeEntry.setPosition(60, 240 + i * 30);
        nameEntry.setPosition(200, 240 + i * 30);
        pointsEntry.setPosition(400, 240 + i * 30);

        placeEntry.setFillColor(sf::Color(0, 0, 0));
        nameEntry.setFillColor(sf::Color(0, 0, 0));
        pointsEntry.setFillColor(sf::Color(0, 0, 0));

        placeEntry.setCharacterSize(20);
        nameEntry.setCharacterSize(20);
        pointsEntry.setCharacterSize(20);

        placeEntry.setFont(font);
        nameEntry.setFont(font);
        pointsEntry.setFont(font);

        window.draw(placeEntry);
        window.draw(nameEntry);
        window.draw(pointsEntry);
    }
}

void Menu::updateMenuButtons(const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData) {
    switch (selectedButton) {
        case ButtonType::new_game: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                lastButton = selectedButton;
            }
            textButtons[0].changeColor(buttonChosenColor);

            playerNick.updateIsFocused(true);

            if (playerNick.getText().empty() || doesFileNameMatch(playerNick.getText())) {
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

            setRankingSideBlock(window, rankingData);
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
                setRankingSideBlock(window, rankingData);
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
    drawSideBlockAndHeadline("rules", window);

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

void Menu::setRankingSideBlock(RenderWindow &window, const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData) {
    drawSideBlockAndHeadline("ranking", window);
    renderRanking(rankingData);
}

void Menu::setLoadGameSideBlock(RenderWindow &window) {
    drawSideBlockAndHeadline("load game", window);
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

bool Menu::doesFileNameMatch(const std::string& partialFileName) {
    std::string lowerCasePartialFileName = partialFileName;
    std::transform(lowerCasePartialFileName.begin(), lowerCasePartialFileName.end(), lowerCasePartialFileName.begin(), ::tolower);

    std::string fileNameToCheck = lowerCasePartialFileName + "_save.csv";

    return isFileInFolder(fileNameToCheck, "../game_saves");
}

bool Menu::isFileInFolder(const std::string& fileName, const std::string& folderPath) {
    std::filesystem::path filePath = std::filesystem::path(folderPath) / fileName;
    return std::filesystem::exists(filePath);
}

void Menu::drawSideBlockAndHeadline(std::string headline, RenderWindow& window){
    sf::RectangleShape sideBlock(sf::Vector2f(250, 370));
    sideBlock.setPosition(40, 110);
    sideBlock.setFillColor(sideBlockColor);
    window.draw(sideBlock);

    sf::Text headlineText;
    headlineText.setString(headline);
    headlineText.setPosition(60, 130);
    headlineText.setFillColor(sf::Color(0, 0, 0));
    headlineText.setCharacterSize(30);
    headlineText.setFont(font);
    window.draw(headlineText);
}