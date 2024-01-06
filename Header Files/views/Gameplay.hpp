#pragma once

#include "../map/MapManager.hpp"
#include "../pawns/Player.hpp"

class Gameplay {
public:
    Gameplay(MapManager *mapManager, Player *player, sf::RenderWindow &window);

    void handleInput();

    void update(float d);
    void updatePlayer(float d);
    void updateMovement(float d);
    void updateJumping(float d);
    void updateMap(float d);
    void render();
    void renderPlayer();
    void renderMap();

    bool checkCollisionWithCells(float x, float y);

    const float jumpSpeed = 400.0f;
    const float gravity = 1000.0f;

private:
    MapManager* mapManager;
    Player* player;
    sf::RenderWindow& window;

};
