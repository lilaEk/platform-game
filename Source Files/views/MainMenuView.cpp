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
    Button newGame = Button("new game", 470, 110, sf::Color(221, 180, 34), this->window, this->font);
    Button loadGame = Button("load game", 700, 110, sf::Color(194, 78, 29), this->window, this->font);
    Button highScores = Button("high scores", 470, 200, sf::Color(140, 82, 255), this->window, this->font);
    Button rules = Button("rules", 700, 200, sf::Color(115, 165, 126), this->window, this->font);
    Button yourCharacter = Button("choose your\ncharacter", Game::width / 2 - 100, Game::height / 2 + 40,
                                  200, 120, sf::Color(213, 232, 236), this->window, this->font);
    Button start = Button("start", 700, 420, sf::Color(151, 164, 166), this->window, this->font);

    buttons.push_back(newGame);
    buttons.push_back(loadGame);
    buttons.push_back(highScores);
    buttons.push_back(rules);
    buttons.push_back(yourCharacter);
    buttons.push_back(start);
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
    for (Button b: buttons) {
        b.render(this->window);
    }
}

void MainMenuView::updateMenuButtons() {
    switch (this->selectedButton) {
        case ButtonType::new_game: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            buttons[0].changeColor(buttonChosenColor);
            buttons[5].changeColor(buttonChosenColor);
            break;
        }
        case ButtonType::load_game: {
            if (lastButton!=selectedButton) {
                resetNotUsingButtons();
                lastButton=selectedButton;
            }
            buttons[1].changeColor(buttonChosenColor);
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
            buttons[2].changeColor(buttonChosenColor);
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
            buttons[3].changeColor(buttonChosenColor);
            sf::RectangleShape rulesSideBlock(sf::Vector2f(250, 370));
            rulesSideBlock.setPosition(40, 110);
            rulesSideBlock.setFillColor(rulesColor);
            window.draw(rulesSideBlock);
            break;
        }
        default:
            break;
    }
}

void MainMenuView::resetNotUsingButtons() {
    buttons[0].changeColor(sf::Color(221, 180, 34));
    buttons[1].changeColor(sf::Color(194, 78, 29));
    buttons[2].changeColor(sf::Color(140, 82, 255));
    buttons[3].changeColor(sf::Color(115, 165, 126));
    buttons[4].changeColor(sf::Color(213, 232, 236));
    buttons[5].changeColor(sf::Color(151, 164, 166));
}
