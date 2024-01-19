#pragma once

#include "Map.hpp"

class Map;

class MapManager {
public:
    MapManager();
    ~MapManager();

    void update();
    void render(sf::RenderWindow &target);

    void scrollMap(float currentTime);

    Map *currentMap;

private:

};
