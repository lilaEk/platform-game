#include <iostream>
#include "../../Header Files/map/Map.hpp"

Map::Map() {
    initMap();
}

Map::~Map() {
}

void Map::initMap() {

    for (int i = 0; i < 25; i++) {
        std::array<Cell, 14> column;

        for (int j = 0; j < 14; j++) {
            Cell cell;
            if (j == 12 || j==13) {
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
//        std::cout << "usunieto kolumne" << std::endl;
        mapData.erase(mapData.begin());
    }

    while (mapData.size() < Map::MaxVisibleColumns) {
//        std::cout << "25 NOWYCH KOLUMN" << std::endl;
        addNextRandomStructure();
    }
}

void Map::renderMap(sf::RenderWindow &target) {

    for (auto &column: mapData) {
        for (Cell &cell: column) {
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
            cell.pos_x -= 400.f * currentTime;
        }
    }
}

void Map::addNextRandomStructure() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomValue = rand() % 2 + 1;

    Cell cell;

    switch (randomValue) {
        case 1:
            for (int i = 0; i < structureColumns; i++) {
                std::array<Cell, 14> newColumn;
                for (int j = 0; j < 14; j++) {

                    if ((i == 4 && j == 4) || (i == 11 && j == 4) || (i == 12 && j == 4)) {
                        cell = Cell(CellType::randomReward);
                    } else if ((i == 9 && j == 4) || (i == 10 && j == 4) || (i == 13 && j == 4) || (i == 14 && j == 4)
                               || (i == 4 && j == 8) || (i == 5 && j == 8) || (i == 6 && j == 8) || (i == 7 && j == 8)
                               || (i == 11 && j == 8) || (i == 12 && j == 8) || (i == 16 && j == 8) ||
                               (i == 17 && j == 8) ||
                               (i == 18 && j == 8)) {
                        cell = Cell(CellType::platform);
                    } else if (j == 12 || j==13) {
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
            break;

        case 2:
            for (int i = 0; i < structureColumns; i++) {
                std::array<Cell, 14> newColumn;
                for (int j = 0; j < 14; j++) {
                    if ((i == 8 && j == 12) || (i == 9 && j == 12) || (i == 10 && j == 12) || (i == 11 && j == 12) || (i == 12 && j == 12)) {
                        cell = Cell(CellType::fire);
                    } else
                        if ((i == 9 && j == 5) || (i == 10 && j == 5) || (i == 11 && j == 5)

                               || (i == 3 && j == 11) || (i == 4 && j == 11) || (i == 5 && j == 11) || (i == 6 && j == 11)|| (i == 7 && j == 11)
                               || (i == 13 && j == 11) || (i == 14 && j == 11) || (i == 15 && j == 11) || (i == 16 && j == 11)|| (i == 17 && j == 11)

                               || (i == 4 && j == 10) || (i == 5 && j == 10) || (i == 6 && j == 10) || (i == 7 && j == 10)
                               || (i == 13 && j == 10) || (i == 14 && j == 10) || (i == 15 && j == 10) || (i == 16 && j == 10)

                               || (i == 5 && j == 9) || (i == 6 && j == 9) || (i == 7 && j == 9)
                               || (i == 13 && j == 9) || (i == 14 && j == 9) || (i == 15 && j == 9)

                               || (i == 6 && j == 8) || (i == 7 && j == 8)
                               || (i == 13 && j == 8) || (i == 14 && j == 8)){
                        cell = Cell(CellType::platform);

                        } else if (j == 12 || j==13) {
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
            break;
//        case 3:
//            std::cout << "Otrzymano wartość 3" << std::endl;
//            break;
//        case 4:
//            std::cout << "Otrzymano wartość 4" << std::endl;
//            break;
//        case 5:
//            std::cout << "Otrzymano wartość 5" << std::endl;
//            break;
//        case 6:
//            std::cout << "Otrzymano wartość 6" << std::endl;
//            break;
//        case 7:
//            std::cout << "Otrzymano wartość 7" << std::endl;
//            break;
//        case 8:
//            std::cout << "Otrzymano wartość 8" << std::endl;
//            break;
        default:
            std::cerr << "Nieprawidłowa wartość" << std::endl;
            break;
    }
}
