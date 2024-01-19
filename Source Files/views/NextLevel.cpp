#include "../../Header Files/views/NextLevel.hpp"
#include "../../Header Files/Game.hpp"

NextLevel::NextLevel(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats)
        : mapManager(mapManager), player(player), window(window), stats(stats) {

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }
}

void NextLevel::update(float deltaTime) {
    updatePlayer(deltaTime);
}

void NextLevel::updatePlayer(float d) {
    player->update(d, false);
}

void NextLevel::render() {
    renderMap();
    renderPlayer();
    renderHeadline();
    renderTextProgressSaved();
    renderTextToContinue();
}

void NextLevel::renderPlayer() {
    player->render(window);
}

void NextLevel::renderMap() {
    mapManager.render(window);
}

void NextLevel::renderHeadline() {
    headline.setString("level " + std::to_string(stats->level));
    headline.setPosition(350, 130);
    headline.setFillColor(sf::Color::Black);
    headline.setCharacterSize(90);
    headline.setFont(font);

    window.draw(headline);
}

void NextLevel::renderTextProgressSaved() {
    if (stats->level == 1) {
        return;
    }

    progressSaved.setString("progress saved!");
    progressSaved.setPosition(400, 250);
    progressSaved.setFillColor(sf::Color::Black);
    progressSaved.setCharacterSize(25);
    progressSaved.setFont(font);

    window.draw(progressSaved);
}

void NextLevel::renderTextToContinue() {
    textToContinue.setString("press ENTER to continue or ESC to go back to menu");
    textToContinue.setPosition(170, 360);
    textToContinue.setFillColor(sf::Color::Black);
    textToContinue.setCharacterSize(25);
    textToContinue.setFont(font);

    window.draw(textToContinue);
}


