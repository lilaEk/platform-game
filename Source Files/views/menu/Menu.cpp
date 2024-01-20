#include "../../../Header Files/views/menu/Menu.hpp"
#include "../../../Header Files/Game.hpp"

Menu::Menu(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats)
        : mapManager(mapManager), player(player), window(window), playerNick(window, font), stats(stats) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }

    init();
}

void Menu::init() {
    initButtons();
    selectedButton = ButtonType::none;
    isStartClickable = false;
}

void Menu::initButtons() {
    Button newGame = Button("new game", 470, 110, upButtonsColor, window, font, ButtonType::new_game);
    Button loadGame = Button("load game", 700, 110, upButtonsColor, window, font, ButtonType::load_game);
    Button highScores = Button("high scores", 470, 200, downButtonsColor, window, font, ButtonType::high_scores);
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

void Menu::update(float deltaTime,
                  const std::vector<std::tuple<std::string, int, int, int, double, std::string>> &rankingData) {
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

void Menu::renderRanking(const std::vector<std::tuple<std::string, int, int, int, double, std::string>> &rankingData) {
    drawSideBlockAndHeadline("ranking", window);

    sf::Text nameHeader, pointsHeader;
    nameHeader.setString("NAME");
    pointsHeader.setString("POINTS");

    nameHeader.setPosition(100, 190);
    pointsHeader.setPosition(200, 190);

    nameHeader.setFillColor(sf::Color(0, 0, 0));
    pointsHeader.setFillColor(sf::Color(0, 0, 0));

    nameHeader.setCharacterSize(20);
    pointsHeader.setCharacterSize(20);

    nameHeader.setFont(font);
    pointsHeader.setFont(font);

    window.draw(nameHeader);
    window.draw(pointsHeader);

    std::vector<sf::Text> texts;

    for (size_t i = 0; i < 10; ++i) {
        std::string placeText, nameText, pointsText;

        if (i < rankingData.size()) {
            const auto &playerTuple = rankingData[i];
            placeText = std::to_string(i + 1) + ".";
            nameText = std::get<0>(playerTuple);
            pointsText = std::to_string(std::get<3>(playerTuple));
        } else {
            placeText = std::to_string(i + 1) + ".";
            nameText = "[empty]";
            pointsText = "0";
        }

        sf::Text placeEntry, nameEntry, pointsEntry, line;

        placeEntry.setString(placeText);
        nameEntry.setString(nameText);
        pointsEntry.setString(pointsText);
        line.setString("----------------------------------");

        placeEntry.setPosition(60, 220 + i * 25);
        nameEntry.setPosition(100, 220 + i * 25);
        pointsEntry.setPosition(200, 220 + i * 25);
        line.setPosition(60, 233 + i * 25);

        placeEntry.setFillColor(sf::Color(0, 0, 0));
        nameEntry.setFillColor(sf::Color(0, 0, 0));
        pointsEntry.setFillColor(sf::Color(0, 0, 0));
        line.setFillColor(sf::Color(0, 0, 0));
        line.setFillColor(sf::Color(0, 0, 0));

        placeEntry.setCharacterSize(16);
        nameEntry.setCharacterSize(16);
        pointsEntry.setCharacterSize(16);
        line.setCharacterSize(16);

        placeEntry.setFont(font);
        nameEntry.setFont(font);
        pointsEntry.setFont(font);
        line.setFont(font);

        window.draw(placeEntry);
        window.draw(nameEntry);
        window.draw(pointsEntry);
        window.draw(line);
    }
}

void Menu::renderGamesToLoad(const std::vector<std::string> &playableGames, const sf::Vector2i &mousePosition) {
    drawSideBlockAndHeadline("load game", window);

    sf::Text nameHeader, pointsHeader, powerHeader, livesHeader;
    nameHeader.setString("NAME");
    pointsHeader.setString("POINTS");
    powerHeader.setString("POWER");
    livesHeader.setString("LIVES");

    nameHeader.setPosition(60, 190);
    pointsHeader.setPosition(140, 190);
    powerHeader.setPosition(220, 190);
    livesHeader.setPosition(300, 190);

    nameHeader.setFillColor(sf::Color(0, 0, 0));
    pointsHeader.setFillColor(sf::Color(0, 0, 0));
    powerHeader.setFillColor(sf::Color(0, 0, 0));
    livesHeader.setFillColor(sf::Color(0, 0, 0));

    nameHeader.setCharacterSize(18);
    pointsHeader.setCharacterSize(18);
    powerHeader.setCharacterSize(18);
    livesHeader.setCharacterSize(18);

    nameHeader.setFont(font);
    pointsHeader.setFont(font);
    powerHeader.setFont(font);
    livesHeader.setFont(font);

    window.draw(nameHeader);
    window.draw(pointsHeader);
    window.draw(powerHeader);
    window.draw(livesHeader);


    for (size_t i = 0; i < 10; ++i) {
        std::string nameText, pointsText, powerText, livesText;

        if (i < playableGames.size()) {
            const std::string &gameFileName = playableGames[i];
            const std::string gameFilePath = "../game_saves/" + gameFileName;

            std::ifstream inputFile(gameFilePath);

            if (inputFile.is_open()) {
                std::string line;
                std::getline(inputFile, line);

                std::string level, power, points, lives, time;
                std::getline(inputFile, nameText, ',');
                std::getline(inputFile, level, ',');
                std::getline(inputFile, power, ',');
                std::getline(inputFile, points, ',');
                std::getline(inputFile, lives, ',');
                std::getline(inputFile, time);

                inputFile.close();

                pointsText = points;
                powerText = power;
                livesText = lives;

                inputFile.close();
            } else {
                std::cerr << "ERROR: Could not open file for reading: " << gameFilePath << std::endl;
                continue;
            }

        } else {
            nameText = "[empty]";
            pointsText = "0";
            powerText = "0";
            livesText = "0";
        }

        sf::Text nameEntry, pointsEntry, powerEntry, livesEntry, line;

        nameEntry.setString(nameText);
        pointsEntry.setString(pointsText);
        powerEntry.setString(powerText);
        livesEntry.setString(livesText);
        line.setString("-----------------------------------------------");

        nameEntry.setPosition(60, 220 + i * 25);
        pointsEntry.setPosition(140, 220 + i * 25);
        powerEntry.setPosition(220, 220 + i * 25);
        livesEntry.setPosition(300, 220 + i * 25);
        line.setPosition(60, 233 + i * 25);

        nameEntry.setFillColor(sf::Color(0, 0, 0));
        pointsEntry.setFillColor(sf::Color(0, 0, 0));
        powerEntry.setFillColor(sf::Color(0, 0, 0));
        livesEntry.setFillColor(sf::Color(0, 0, 0));
        line.setFillColor(sf::Color(0, 0, 0));

        if (((xChosenGame == 0 && yChosenGame == 0) &&
             (mousePosition.y >= 220 + i * 25 && mousePosition.y <= 220 + (i + 1) * 25 &&
              mousePosition.x >= 60 && mousePosition.x <= 300))
            || (yChosenGame >= 220 + i * 25 && yChosenGame <= 220 + (i + 1) * 25 &&
                xChosenGame >= 60 && xChosenGame <= 300)) {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                xChosenGame = mousePosition.x;
                yChosenGame = mousePosition.y;

                gameChooseToLoad = true;
                isStartClickable = true;
                textButtons[5].changeColor(buttonChosenColor);

                loadGameDataFromSave(nameText);

            }
            nameEntry.setFillColor(buttonChosenColor);
            pointsEntry.setFillColor(buttonChosenColor);
            powerEntry.setFillColor(buttonChosenColor);
            livesEntry.setFillColor(buttonChosenColor);
            line.setFillColor(buttonChosenColor);
        }

        nameEntry.setCharacterSize(16);
        pointsEntry.setCharacterSize(16);
        powerEntry.setCharacterSize(16);
        livesEntry.setCharacterSize(16);
        line.setCharacterSize(16);

        nameEntry.setFont(font);
        pointsEntry.setFont(font);
        powerEntry.setFont(font);
        livesEntry.setFont(font);
        line.setFont(font);

        window.draw(nameEntry);
        window.draw(pointsEntry);
        window.draw(powerEntry);
        window.draw(livesEntry);
        window.draw(line);
    }
}

void Menu::updateMenuButtons(const std::vector<std::tuple<std::string, int, int, int, double, std::string>> &rankingData) {
    switch (selectedButton) {
        case ButtonType::new_game: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                resetLoadGameValues();
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
                resetLoadGameValues();
                lastButton = selectedButton;
            }
            textButtons[1].changeColor(buttonChosenColor);

            setLoadGameSideBlock(window);
            break;
        }
        case ButtonType::high_scores: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                resetLoadGameValues();
                lastButton = selectedButton;
            }
            textButtons[2].changeColor(buttonChosenColor);

            setRankingSideBlock(window, rankingData);
            break;
        }
        case ButtonType::rules: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                resetLoadGameValues();
                lastButton = selectedButton;
            }
            textButtons[3].changeColor(buttonChosenColor);

            setRulesSideBlock(window, font);
            break;
        }
        case ButtonType::choose_your_character: {
            if (lastButton != selectedButton) {
                resetNotUsingButtons();
                resetLoadGameValues();
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
                lastButton = ButtonType::none;
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
    if (mouseX >= 60 && mouseX <= 300 && mouseY >= 220 && mouseY <= 470) {
        size_t rowIndex = static_cast<size_t>((mouseY - 220) / 25);

        if (rowIndex < getPlayableGames().size()) {
            std::string selectedGameName = getPlayableGames()[rowIndex];
        }
    } else {
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

void Menu::setRankingSideBlock(RenderWindow &window,
                               const std::vector<std::tuple<std::string, int, int, int, double, std::string>> &rankingData) {
    drawSideBlockAndHeadline("ranking", window);
    renderRanking(rankingData);
}

void Menu::setLoadGameSideBlock(RenderWindow &window) {
    sf::RectangleShape sideBlock(sf::Vector2f(320, 380));
    sideBlock.setPosition(40, 110);
    sideBlock.setFillColor(sideBlockColor);
    window.draw(sideBlock);

    sf::Text headlineText;
    headlineText.setString("load game");
    headlineText.setPosition(60, 130);
    headlineText.setFillColor(sf::Color(0, 0, 0));
    headlineText.setCharacterSize(30);
    headlineText.setFont(font);
    window.draw(headlineText);

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    renderGamesToLoad(getPlayableGames(), mousePosition);
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

bool Menu::doesFileNameMatch(const std::string &partialFileName) {
    std::string lowerCasePartialFileName = partialFileName;
    std::transform(lowerCasePartialFileName.begin(), lowerCasePartialFileName.end(), lowerCasePartialFileName.begin(),
                   ::tolower);

    std::string fileNameToCheck = lowerCasePartialFileName + "_save.csv";

    return isFileInFolder(fileNameToCheck, "../game_saves");
}

bool Menu::isFileInFolder(const std::string &fileName, const std::string &folderPath) {
    std::filesystem::path filePath = std::filesystem::path(folderPath) / fileName;
    return std::filesystem::exists(filePath);
}

void Menu::drawSideBlockAndHeadline(std::string headline, RenderWindow &window) {
    sf::RectangleShape sideBlock(sf::Vector2f(250, 380));
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

std::vector<std::string> Menu::getPlayableGames() {
    std::vector<std::string> playableGames;

    for (const auto &entry: std::filesystem::directory_iterator("../game_saves")) {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {

            std::string filePath = entry.path().string();
            std::replace(filePath.begin(), filePath.end(), '\\', '/');

            std::ifstream inputFile(filePath);

            if (inputFile.is_open()) {
                std::string playerName;
                int level, power, points;
                double lives;
                std::string time;

                std::string line;

                if (std::getline(inputFile, line)) {
                    while (std::getline(inputFile, line)) {
                        std::istringstream iss(line);
                        char comma;

                        if (std::getline(iss, playerName, ',') &&
                            iss >> level >> comma >> power >> comma >> points >> comma >> lives >> comma >> time) {

                            playableGames.push_back(entry.path().filename().string());
                        } else {
                            std::cerr << "ERROR: Failed to read data from file: " << filePath << std::endl;
                            continue;
                        }
                    }
                } else {
                    std::cerr << "ERROR: Failed to read data from file: " << entry.path() << std::endl;
                }
            }
        }
    }
    return playableGames;
}

void Menu::resetLoadGameValues() {
    xChosenGame = 0;
    yChosenGame = 0;
    gameChooseToLoad = false;
}

void Menu::loadGameDataFromSave(const std::string &gameFileName) {
    const std::string gameFilePath = "../game_saves/" + gameFileName+"_save.csv";

    std::ifstream inputFile(gameFilePath);

    if (inputFile.is_open()) {

        std::string playerName;
        int level, power, points;
        double lives;
        std::string time;

        std::string line;
        if (std::getline(inputFile, line)) {
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                char comma;

                if (std::getline(iss, playerName, ',') &&
                    iss >> level >> comma >> power >> comma >> points >> comma >> lives >> comma >> time) {

                    nick=gameFileName;
                    stats->level = level;
                    stats->points = points;
                    stats->power = power;
                    stats->lives = lives;
                }
            }
        } else {
            std::cerr << "ERROR: Could not open file for reading: " << gameFilePath << std::endl;
        }
    }
}