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
    void addNextColumn(int count);

    void scrollMap(float currentTime);

    std::vector<std::array<Cell, 12>> mapData;

    const int MaxVisibleColumns = 21;
    int scrolledColumns=0;

    int index=1;
};