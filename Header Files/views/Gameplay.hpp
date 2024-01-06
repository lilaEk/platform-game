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

    const float jumpSpeed = 600.0f;
    const float gravity = 800.0f;

private:
    MapManager* mapManager;
    Player* player;
    sf::RenderWindow& window;

    bool noKeyIsPressed = !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
                          !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
                          !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) &&
                          !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) &&
                          !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

};
