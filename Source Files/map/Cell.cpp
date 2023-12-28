#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width=cellSize;
    this->height=cellSize;

    switch (type) {
        case CellType::platform:
            this->cellType=CellType::platform;

            break;
        default: //case empty
            this->cellType=CellType::empty;
            break;
    }
}

void Cell::render(sf::RenderTarget &target)  {
    target.draw(this->sprite);
}

Cell::Cell() {
}
