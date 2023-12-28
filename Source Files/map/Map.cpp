#include "../../Header Files/map/Map.hpp"

Map::Map() {
    initMap();
}

Map::~Map() {
}

void Map::initMap() {
    for (int i = 0; i < 20; i++) {
        std::array<Cell, 12> column;
        for (int j = 0; j < 12; j++) {
            if (i == 12-1) {
                column[j] = Cell(CellType::platform);
                continue;
            }
            column[j] = Cell(CellType::empty);
        }
        mapData.push_back(column);
    }
}

void Map::updateMap(float deltaTime) {
}

void Map::renderMap(sf::RenderWindow &target) {
}