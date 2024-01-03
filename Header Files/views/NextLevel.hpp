#pragma once

#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"

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
