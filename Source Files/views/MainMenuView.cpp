#include "../../Header Files/views/MainMenuView.hpp"


MainMenuView::MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

}

void MainMenuView::init() {

}

void MainMenuView::handleInput() {

}

void MainMenuView::update(float deltaTime) {
    updateMap(deltaTime);
    updatePlayer(deltaTime);

}

void MainMenuView::updatePlayer(float d) {
    this->player.update(d);
}

void MainMenuView::updateMap(float d) {

}

void MainMenuView::render() {
    this->renderMap();
    this->renderPlayer();
}

void MainMenuView::renderPlayer() {
    this->player.render(this->window);

}

void MainMenuView::renderMap() {
    this->mapManager.render(this->window);

}
