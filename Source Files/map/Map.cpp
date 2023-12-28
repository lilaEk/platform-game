#include <iostream>
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
            Cell cell;
            if (i == 12 - 1) {
                cell = Cell(CellType::platform);
            } else {
                cell = Cell(CellType::empty);
            }
            cell.pos_x = j * Cell::cellSize;
            cell.pos_y = i * Cell::cellSize-Cell::cellSize;

            if (i==11){
            std::cout << "("<<cell.pos_x << ","<<cell.pos_y<<")"<<std::endl;}
        }

        mapData.push_back(column);
    }
}

void Map::updateMap(float deltaTime) {
}

void Map::renderMap(sf::RenderWindow &target) {

    for (auto &column: mapData) {
        for (Cell &cell: column) {
            cell.render(target);
        }
    }
}