#pragma once

#include "../map/MapManager.hpp"
#include "../pawns/Player.hpp"

class GameOver {
public:
    GameOver(MapManager &mapManager, Player &player, sf::RenderWindow &window);

    void handleInput();

    void update(float d);
    void updatePlayer(float d);
    void render();
    void renderPlayer();
    void renderMap();

private:
    MapManager& mapManager;
    Player& player;
    sf::RenderWindow& window;
};

