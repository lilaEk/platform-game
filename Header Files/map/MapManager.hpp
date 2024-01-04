#pragma once

#include "Map.hpp"

class Map;

class MapManager {
public:
    MapManager();
    ~MapManager();

//    void loadMap(const std::string &mapName);
//    void switchMap(const std::string &mapName);

    void update(float deltaTime);
    void render(sf::RenderWindow &target);

    void scrollMap(float currentTime);

    Map *currentMap;

private:
//    std::unordered_map<std::string, Map> maps;
//    Map *currentMap;
};
