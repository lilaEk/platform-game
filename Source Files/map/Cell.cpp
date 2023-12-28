#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width=cellSize;
    this->height=cellSize;

    this->scale=1.f;

    switch (type) {
        case CellType::platform:
            if (!this->texture.loadFromFile("../assets/elements/brick.png")) {
                std::cerr << "ERROR: Could not load platform texture from file\n";
            } else {
                this->sprite.setTexture(this->texture);
            }
            this->cellType=CellType::platform;
            break;
        default: //case empty
            this->cellType=CellType::empty;
            break;
    }
    this->sprite.setScale(this->scale, this->scale);
}

void Cell::render(sf::RenderTarget &target)  {
    target.draw(this->sprite);
}

Cell::Cell() {
}
