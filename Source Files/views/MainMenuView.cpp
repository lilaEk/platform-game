#include "../../Header Files/views/MainMenuView.hpp"
#include "../../Header Files/Game.hpp"

MainMenuView::MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }

    initButtons(this->font);

    sf::Text text;
    text.setString("platform game by rozalia");
    text.setPosition(100, 250);
    text.setFillColor(sf::Color(0,0,0));
    text.setCharacterSize(30);
    text.setFont(font);

    window.draw(text);

}

void MainMenuView::handleInput() {

}

void MainMenuView::initButtons(sf::Font font) {
    Button newGame = Button("new game", 470, 110, sf::Color(221, 180, 34), this->window, this->font);
    Button loadGame = Button("load game", 700, 110, sf::Color(194, 78, 29), this->window, this->font);
    Button highScores = Button("high scores", 470, 200, sf::Color(140, 82, 255), this->window, this->font);
    Button rules = Button("rules", 700, 200, sf::Color(115, 165, 126), this->window, this->font);
    Button yourCharacter = Button("choose your\ncharacter", Game::width/2-100, Game::height/2+40,
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
    updatePlayer(deltaTime);

}

void MainMenuView::updatePlayer(float d) {
    this->player.update(d, false);
}


void MainMenuView::render() {
    this->renderMap();
    this->renderPlayer();
    this->renderButtons();
}

void MainMenuView::renderPlayer() {
    this->player.render(this->window);

}

void MainMenuView::renderMap() {
    this->mapManager.render(this->window);

}

void MainMenuView::renderButtons() {
    for (Button b : buttons){
        b.render(this->window);
    }
}
