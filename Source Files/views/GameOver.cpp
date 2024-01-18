#include "../../Header Files/views/GameOver.hpp"

GameOver::GameOver(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats)
        : mapManager(mapManager), player(player), window(window), stats(stats) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }
}

void GameOver::update(float deltaTime) {
    updatePlayer(deltaTime);
}

void GameOver::updatePlayer(float d) {
    player->update(d, false);
}

void GameOver::render() {
    renderMap();
    renderPlayer();
    renderHeadline();
    renderTextProgressSaved();
    renderTextToContinue();
}

void GameOver::renderPlayer() {
    this->player->render(this->window);
}

void GameOver::renderMap() {
    this->mapManager.render(this->window);
}

void GameOver::renderHeadline() {
    headline.setString("game over");
    headline.setPosition(290, 50);
    headline.setFillColor(sf::Color::Black);
    headline.setCharacterSize(90);
    headline.setFont(font);

    window.draw(headline);
}

void GameOver::renderTextProgressSaved() {
    progressSaved.setString("progress saved at level " + std::to_string(stats->level));
    progressSaved.setPosition(350, 180);
    progressSaved.setFillColor(sf::Color::Black);
    progressSaved.setCharacterSize(25);
    progressSaved.setFont(font);

    window.draw(progressSaved);
}

void GameOver::renderTextToContinue() {
    textToContinue.setString("press ESC to go back to menu");
    textToContinue.setPosition(300, 260);
    textToContinue.setFillColor(sf::Color::Black);
    textToContinue.setCharacterSize(25);
    textToContinue.setFont(font);

    window.draw(textToContinue);
}

void GameOver::setKeyCallback(KeyCallback callback) {
    keyCallback = std::move(callback);
}