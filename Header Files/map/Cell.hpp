#pragma once

#include <iostream>
#include <vector>
#include <array>
#include "SFML/Graphics/RenderWindow.hpp"
#include "CellType.hpp"
#include "../pawns/Entity.hpp"

class Cell : public Entity {

public:
    Cell();
    explicit Cell(CellType type);
    static const int cellSize = 48;

    void render(sf::RenderTarget &target) override;

    void changeCellType(CellType cellType);

    sf::FloatRect getBoundingBox();

    CellType cellType;
};