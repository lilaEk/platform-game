#pragma once

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Cell.hpp"
#include "../pawns/Enemy.hpp"

class Cell;

class Map {
public:
    Map();
    ~Map();

    void initMap();
    void updateMap(Enemy &enemy);
    void renderMap(sf::RenderWindow &target);

    void scrollMap(float currentTime,Enemy &enemy);

    std::vector<std::array<Cell, 14>> mapData;

    const int MaxVisibleColumns = 21+2;
    int scrolledColumns=0;

    void setMapStructure(std::vector<std::array<int, 14>> structure,Enemy &enemy);
    void addNextRandomStructure(Enemy &enemy);

    void generateSnakeAtX(int i,Enemy &enemy);
};