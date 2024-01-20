#pragma once

#include "Map.hpp"
#include "../pawns/Enemy.hpp"

class Map;

class MapManager {
public:
    MapManager();
    ~MapManager();

    void update(Enemy& enemy);
    void render(sf::RenderWindow &target);

    void scrollMap(float currentTime,Enemy &enemy);

    Map *currentMap;
};
