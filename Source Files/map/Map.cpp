#include <iostream>
#include "../../Header Files/map/Map.hpp"

Map::Map() {
    initMap();
}

Map::~Map() {
}

void Map::initMap() {
    std::vector<std::array<int, 14>> structure = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
    };

    Cell cell;

    for (int i = 0; i < 25; i++) {
        std::array<Cell, 14> column;

        for (int j = 0; j < 14; j++) {

            if (structure[i][j] == 1) {
                cell = Cell(CellType::platform);
            } else if (structure[i][j] == 2) {
                cell = Cell(CellType::randomReward);
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

    std::vector<std::array<int, 14>> structure;
    Cell cell;

    switch (randomValue) {
        case 1: {
            structure = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
            };
            setMapStructure(structure);
            break;
        }
        case 2: {
            structure = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1},
                    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 1},
                    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 1},
                    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
            };
            setMapStructure(structure);
            break;
        }
//        case 3:
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

void Map::setMapStructure(std::vector<std::array<int, 14>> structure) {

    Cell cell;

    for (int i = 0; i < 25; i++) {
        std::array<Cell, 14> column;

        for (int j = 0; j < 14; j++) {

            if (structure[i][j] == 1) {
                cell = Cell(CellType::platform);
            } else if (structure[i][j] == 2) {
                cell = Cell(CellType::randomReward);
            } else if (structure[i][j] == 3) {
                cell = Cell(CellType::fire);
            } else {
                cell = Cell(CellType::empty);
            }

            cell.pos_x = (mapData.size() - 1) * Cell::cellSize;
            cell.pos_y = j * Cell::cellSize;

            column[j] = cell;
        }
        mapData.push_back(column);
    }
}
