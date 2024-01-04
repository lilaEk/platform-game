#include <iostream>
#include "../../Header Files/map/Map.hpp"

Map::Map() {
    initMap();
}

Map::~Map() {
}

void Map::initMap() {

    for (int i = 0; i < 40; i++) {
        std::array<Cell, 12> column;

        for (int j = 0; j < 12; j++) {
            Cell cell;
            if (j == 12 - 1) {
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

void Map::updateMap(float deltaTime) {

    if (!mapData.empty() && mapData.front().front().pos_x + Cell::cellSize <= 0.f) {
        mapData.erase(mapData.begin());
    }

    while (mapData.size() < Map::MaxVisibleColumns) {
        addNextColumn(20);
    }
}

void Map::renderMap(sf::RenderWindow &target) {

    int visibleColumns = std::min(Map::MaxVisibleColumns, static_cast<int>(mapData.size()));

    for (int i = 0; i < visibleColumns; i++) {
        auto &column = mapData[i];

        for (Cell &cell: column) {
            cell.sprite.setPosition(cell.pos_x, cell.pos_y);

            if (cell.cellType == CellType::platform) {
                cell.scale = 1.f;
                cell.sprite.setScale(cell.scale, cell.scale);
                cell.sprite.setPosition(cell.pos_x, cell.pos_y);

                if (!cell.texture.loadFromFile("../assets/elements/brick.png")) {
                    std::cerr << "ERROR: Could not load platform texture from file\n";
                } else {
                    cell.sprite.setTexture(cell.texture);
                }

                cell.render(target);
            }
        }
    }
}

void Map::scrollMap(float currentTime) {

    int firstColumn = static_cast<int>(-mapData.front().front().pos_x / Cell::cellSize);
    if (firstColumn > scrolledColumns) {
        mapData.erase(mapData.begin(), mapData.begin() + (firstColumn - scrolledColumns));
        scrolledColumns = firstColumn;
    }

    for (auto &column : mapData) {
        for (Cell &cell : column) {
            cell.pos_x -= 350.f * currentTime;
        }
    }
}

void Map::addNextColumn(int count) {
    for (int i = 0; i < count; i++) {
        std::array<Cell, 12> newColumn;
        for (int j = 0; j < 12; j++) {
            Cell cell;
            if (j == 12 - 1) {
                cell = Cell(CellType::platform);
            } else {
                cell = Cell(CellType::empty);
            }
            cell.pos_x = (mapData.size() - 1) * Cell::cellSize;
            cell.pos_y = j * Cell::cellSize;
            newColumn[j] = cell;
        }

        mapData.push_back(newColumn);
        std::cout << "dodano kolumne " << this->index++ << std::endl;
    }

}

void Map::addNextRandomStructure() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomValue = rand() % 8 + 1;

    switch (randomValue) { //tutaj generuje sstruktury
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
