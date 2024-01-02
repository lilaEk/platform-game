#pragma once

#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"

class GameOverView {
public:
    GameOverView(MapManager &mapManager, Player &player, sf::RenderWindow &window);

    void init(); // Inicjalizuje widok game over
    void handleInput(); // Obsługuje wejście
    void update(float deltaTime); // Aktualizuje logikę
    void render(); // Renderuje obiekty

private:
    MapManager& mapManager;
    Player& player;
    sf::RenderWindow& window;
};
