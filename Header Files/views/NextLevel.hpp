#pragma once

#include "../pawns/Player.hpp"
#include "../map/MapManager.hpp"

class NextLevel {
public:
    NextLevel(MapManager &mapManager, Player &player, sf::RenderWindow &window);

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
