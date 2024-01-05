#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width = cellSize;
    this->height = cellSize;

    this->cellType = type;
}

Cell::Cell() { }

void Cell::render(sf::RenderTarget &target) {
    if (this->cellType == CellType::empty) {
        return;
    }

    this->scale = 1.f;
    this->sprite.setScale(this->scale, this->scale);
    this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    this->sprite.setPosition(this->pos_x, this->pos_y);

    if (this->cellType == CellType::platform) {
        if (!this->texture.loadFromFile("../assets/blocks/brick.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    } else if (this->cellType == CellType::randomReward) {
        if (!this->texture.loadFromFile("../assets/blocks/questionMarkBlock.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    } else if (this->cellType == CellType::fire) {
        if (!this->texture.loadFromFile("../assets/blocks/fire.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    } else if (this->cellType == CellType::debbug) {
        if (!this->texture.loadFromFile("../assets/blocks/debbug.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }

    target.draw(this->sprite);
}

sf::FloatRect Cell::getBoundingBox() {
    return sf::FloatRect(this->pos_x, this->pos_y, Cell::cellSize * this->scale, Cell::cellSize * this->scale);
}

void Cell::changeCellType(CellType cellType){
    this->cellType = cellType;
}