#pragma once

#include "../map/MapManager.hpp"
#include "../pawns/Player.hpp"
#include "../Stats.hpp"
#include "../pawns/Enemy.hpp"

class Gameplay {
public:

    Gameplay(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats, Enemy *enemy);

    void handleInput();

    void update(float d);
    void updatePlayer(float d);
    void updateEnemies(float d);
    void updateMovement(float d);
    void updateJumping(float d);
    void updateMap(float d);
    void render();
    void renderPlayer();
    void renderEnemies();
    void renderMap();
    void renderStats();

    bool checkCollisionWithCells(float x, float y, bool ifPlayer);

    const float jumpSpeed = 800.0f;
    const float gravity = 1000.0f;

private:
    MapManager& mapManager;
    Player* player;
    sf::RenderWindow& window;
    Stats* stats;
    Enemy* enemy;

    void handleEnemyCollisions();

    bool checkCollisionWithWalls(Enemy &enemy);
    bool checkCollisionWithPit(Enemy &enemy);
    bool checkCollisionWithPlayer(Enemy &enemy, Player &player);

    void playerHurt(int loss);
};
