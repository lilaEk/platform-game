#pragma once

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Cell.hpp"

class Cell;

class Map {
public:
    Map();
    ~Map();

    void initMap();
    void updateMap();
    void renderMap(sf::RenderWindow &target);

    void addNextRandomStructure();

    void scrollMap(float currentTime);

    std::vector<std::array<Cell, 13>> mapData;

    const int MaxVisibleColumns = 21;
    int scrolledColumns=0;

    int structureColumns=25;

};