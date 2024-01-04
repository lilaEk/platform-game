#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width = cellSize;
    this->height = cellSize;

    this->cellType = type;
}

void Cell::render(sf::RenderTarget &target) {
    if (this->cellType == CellType::empty) {
        return;
    }

    this->scale = 1.f;
    this->sprite.setScale(this->scale, this->scale);
    this->sprite.setPosition(this->pos_x, this->pos_y);

    if (this->cellType == CellType::platform) {
        if (!this->texture.loadFromFile("../assets/elements/brick.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    } else if (this->cellType == CellType::randomReward) {
        if (!this->texture.loadFromFile("../assets/elements/questionMarkBlock.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }

    target.draw(this->sprite);
}


Cell::Cell() {
}
