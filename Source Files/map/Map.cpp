#include <iostream>
#include "../../Header Files/map/Map.hpp"

Map::Map() {
    initMap();
}

Map::~Map() {
}

void Map::initMap() {

    for (int i = 0; i < 40; i++) {
        std::array<Cell, 13> column;

        for (int j = 0; j < 13; j++) {
            Cell cell;
            if (j == 13 - 1) {
                cell = Cell(CellType::platform);
            } else {
                cell = Cell(CellType::empty);
            }
            cell.pos_x = i * Cell::cellSize;
            cell.pos_y = j * Cell::cellSize;

            column[j] = cell;
        }
        mapData.push_back(column);
    }
}

void Map::updateMap() {

    if (!mapData.empty() && mapData.front().front().pos_x + Cell::cellSize <= 0.f) {
        std::cout << "usunieto kolumne" << std::endl;
        mapData.erase(mapData.begin());
    }

    while (mapData.size() < Map::MaxVisibleColumns) {
        std::cout << "20 NOWYCH KOLUMN" << std::endl;
        addNextColumn(20);
    }
}

void Map::renderMap(sf::RenderWindow &target) {

    for (auto &column : mapData) {
        for (Cell &cell : column) {
            cell.render(target);
        }
    }
}

void Map::scrollMap(float currentTime) {

    int firstColumn = static_cast<int>(-mapData.front().front().pos_x / Cell::cellSize);
    if (firstColumn > scrolledColumns) {
        mapData.erase(mapData.begin(), mapData.begin() + (firstColumn - scrolledColumns));
        scrolledColumns = firstColumn;
    }

    for (auto &column: mapData) {
        for (Cell &cell: column) {
            cell.pos_x -= 350.f * currentTime;
        }
    }
}

void Map::addNextColumn(int count) {
    for (int i = 0; i < count; i++) {
        std::array<Cell, 13> newColumn;
        for (int j = 0; j < 13; j++) {
            Cell cell;
            if (j == 13 - 1) {
                cell = Cell(CellType::platform);
            } else {
                cell = Cell(CellType::empty);
            }
            cell.pos_x = (mapData.size() - 1) * Cell::cellSize;
            cell.pos_y = j * Cell::cellSize;
            newColumn[j] = cell;
        }
        mapData.push_back(newColumn);
    }
}

void Map::addNextRandomStructure() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomValue = rand() % 8 + 1;

    switch (randomValue) {
        case 1:
            std::cout << "Otrzymano wartość 1" << std::endl;
            break;
        case 2:
            std::cout << "Otrzymano wartość 2" << std::endl;
            break;
        case 3:
            std::cout << "Otrzymano wartość 3" << std::endl;
            break;
        case 4:
            std::cout << "Otrzymano wartość 4" << std::endl;
            break;
        case 5:
            std::cout << "Otrzymano wartość 5" << std::endl;
            break;
        case 6:
            std::cout << "Otrzymano wartość 6" << std::endl;
            break;
        case 7:
            std::cout << "Otrzymano wartość 7" << std::endl;
            break;
        case 8:
            std::cout << "Otrzymano wartość 8" << std::endl;
            break;
        default:
            std::cerr << "Nieprawidłowa wartość" << std::endl;
            break;
    }

}
