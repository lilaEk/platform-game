#include "../../Header Files/views/Gameplay.hpp"


Gameplay::Gameplay(MapManager *mapManager, Player *player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

}

void Gameplay::handleInput() {
//    sf::Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed) {
//            window.close();
//        } else if (event.type == sf::Event::KeyPressed) {
//            if (event.key.code == sf::Keyboard::Key::A || event.key.code == sf::Keyboard::Key::Left) {
//                // Obsługa ruchu w lewo
//            } else if (event.key.code == sf::Keyboard::Key::D || event.key.code == sf::Keyboard::Key::Right) {
//                // Obsługa ruchu w prawo
//            } else if (event.key.code == sf::Keyboard::Key::W || event.key.code == sf::Keyboard::Key::Up) {
//                // Obsługa skoku
//            } else if (event.key.code == sf::Keyboard::Key::S || event.key.code == sf::Keyboard::Key::Down) {
//                // Obsługa kucania/rolowania
//            }
//            // Dodaj obsługę innych klawiszy według potrzeb
//        }
//    }

}

void Gameplay::update(float deltaTime) {
    updateMap(deltaTime);
    updatePlayer(deltaTime);
}

void Gameplay::updatePlayer(float d) {
    this->player->update(d, true);
}

void Gameplay::updateMap(float d) {
    this->mapManager->update(d);
}

void Gameplay::render() {
    renderMap();
    renderPlayer();
}

void Gameplay::renderPlayer() {
    this->player->render(this->window);
}

void Gameplay::renderMap() {
    this->mapManager->render(this->window);
}
