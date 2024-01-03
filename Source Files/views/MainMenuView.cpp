#include "../../Header Files/views/MainMenuView.hpp"
#include "../../Header Files/Game.hpp"

MainMenuView::MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }

    initButtons(this->font);
    selectedButton = ButtonType::none;
}

void MainMenuView::handleInput() {

}

void MainMenuView::initButtons(sf::Font font) {
    Button newGame = Button("new game", 470, 110, sf::Color(221, 180, 34), this->window, this->font, ButtonType::new_game);
    Button loadGame = Button("load game", 700, 110, sf::Color(194, 78, 29), this->window, this->font, ButtonType::load_game);
    Button highScores = Button("high scores", 470, 200, sf::Color(140, 82, 255), this->window, this->font, ButtonType::high_scores);
    Button rules = Button("rules", 700, 200, sf::Color(115, 165, 126), this->window, this->font, ButtonType::rules);
    Button yourCharacter = Button("choose your\ncharacter", Game::width / 2 - 100, Game::height / 2 + 40,
                                  200, 120, sf::Color(213, 232, 236), this->window, this->font, ButtonType::choose_your_character);
    Button start = Button("start", 700, 420, sf::Color(151, 164, 166), this->window, this->font, ButtonType::start);

    textButtons.push_back(newGame);
    textButtons.push_back(loadGame);
    textButtons.push_back(highScores);
    textButtons.push_back(rules);
    textButtons.push_back(yourCharacter);
    textButtons.push_back(start);

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("../assets/menu_elements/arrow.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    Button arrow = Button(buttonTexture, Game::width / 2+110, Game::height / 2 + 40, this->window, ButtonType::choose_your_character);
    picButtons.push_back(arrow);
}

void MainMenuView::update(float deltaTime) {
    this->updatePlayer(deltaTime);
    this->updateMenuButtons();
}

void MainMenuView::updatePlayer(float d) {
    this->player.update(d, false);
}

void MainMenuView::render() {
    this->renderMap();
    this->renderPlayer();
    this->renderButtons();
    this->renderHeadline();
}

void MainMenuView::renderHeadline() {

    this->headline.setString(this->headlineText);
    this->headline.setPosition(40, 30);
    this->headline.setFillColor(sf::Color(0, 0, 0));
    this->headline.setCharacterSize(40);
    this->headline.setFont(this->font);

    window.draw(this->headline);
}

void MainMenuView::renderPlayer() {
    this->player.render(this->window);
}

void MainMenuView::renderMap() {
    this->mapManager.render(this->window);
}

void MainMenuView::renderButtons() {
    for (Button b: textButtons) {
        b.renderTextButtons(this->window);
    }
    for (Button b: picButtons) {
        b.renderPicButtons(this->window);
    }
}

void MainMenuView::updateMenuButtons() {
    switch (this->selectedButton) {
        case ButtonType::new_game: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            textButtons[0].changeColor(buttonChosenColor);
            textButtons[5].changeColor(buttonChosenColor);
            break;
        }
        case ButtonType::load_game: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            textButtons[1].changeColor(buttonChosenColor);
            sf::RectangleShape loadGameSideBlock(sf::Vector2f(250, 370));
            loadGameSideBlock.setPosition(40, 110);
            loadGameSideBlock.setFillColor(loadGameColor);
            window.draw(loadGameSideBlock);
            break;
        }
        case ButtonType::high_scores: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            textButtons[2].changeColor(buttonChosenColor);
            sf::RectangleShape highScoresSideBlock(sf::Vector2f(250, 370));
            highScoresSideBlock.setPosition(40, 110);
            highScoresSideBlock.setFillColor(rankingColor);
            window.draw(highScoresSideBlock);
            break;
        }
        case ButtonType::rules: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            textButtons[3].changeColor(buttonChosenColor);

            setRulesSideBlock(this->rulesColor, this->window, this->font);

            break;
        }
        case ButtonType::choose_your_character: {}
        case ButtonType::start: {}

        default:
            break;
    }
}

void MainMenuView::resetNotUsingButtons() {
    textButtons[0].changeColor(sf::Color(221, 180, 34));
    textButtons[1].changeColor(sf::Color(194, 78, 29));
    textButtons[2].changeColor(sf::Color(140, 82, 255));
    textButtons[3].changeColor(sf::Color(115, 165, 126));
    textButtons[4].changeColor(sf::Color(213, 232, 236));
    textButtons[5].changeColor(sf::Color(151, 164, 166));
}

void MainMenuView::handleButtonClick(int mouseX, int mouseY) {
    if (picButtons[0].isClicked(mouseX, mouseY)) {
        this->selectedButton=picButtons[0].getButtonType();
        return;
    }
    for (Button &button: textButtons) {
        if (button.isClicked(mouseX, mouseY)) {
            this->selectedButton=button.getButtonType();
            break;
        }
    }
}

void MainMenuView::setRulesSideBlock(sf::Color rulesColor, RenderWindow& window, Font font){
    sf::RectangleShape rulesSideBlock(sf::Vector2f(250, 370));
    rulesSideBlock.setPosition(40, 110);
    rulesSideBlock.setFillColor(rulesColor);
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