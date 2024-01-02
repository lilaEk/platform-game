#pragma once

#include "../stdafx.hpp"
#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"

class MainMenuView {
public:
public:
    MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window);

    void init();
    void handleInput();
    void update(float d);
    void updatePlayer(float d);
    void updateMap(float d);
    void render();
    void renderPlayer();
    void renderMap();

private:
    MapManager& mapManager;
    Player& player;
    sf::RenderWindow& window;
};

