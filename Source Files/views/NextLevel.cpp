#include "../../Header Files/views/NextLevel.hpp"

NextLevel::NextLevel(MapManager &mapManager, Player *player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

}


void NextLevel::handleInput() {

}

void NextLevel::update(float deltaTime) {
    this->updatePlayer(deltaTime);
}

void NextLevel::updatePlayer(float d) {
    this->player->update(d, false);
}

void NextLevel::render() {
    this->renderMap();
    this->renderPlayer();
}

void NextLevel::renderPlayer() {

}

void NextLevel::renderMap() {

}

void NextLevel::renderTextProgressSaved() {

}

void NextLevel::renderTextToContinue() {

}

void NextLevel::renderHeadline() {

}