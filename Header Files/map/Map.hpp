#pragma once

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Cell.hpp"

class Cell;

class Map {
public:
    Map();
    ~Map();

    void updateMap(float deltaTime);
    void renderMap(sf::RenderWindow &target);

    std::vector<std::array<Cell, 12>> mapData; //array 12

private:
    void initMap();

};