#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width=cellSize;
    this->height=cellSize;

    switch (type) {
        case CellType::platform:
            this->cellType=CellType::platform;

//            this->scale = 1.f;
//            this->sprite.setScale(this->scale,this->scale);
//            this->sprite.setPosition(this->pos_x, this->pos_y);
//
//            if (!this->texture.loadFromFile("../assets/elements/brick.png")) {
//                std::cerr << "ERROR: Could not load platform texture from file\n";
//            } else {
//                this->sprite.setTexture(this->texture);
//            }

            break;
        default: //case empty
            this->cellType=CellType::empty;
            break;
    }
}

void Cell::render(sf::RenderTarget &target)  {
    if (this->cellType == CellType::platform) {
        this->scale = 1.f;
        this->sprite.setScale(this->scale, this->scale);
        this->sprite.setPosition(this->pos_x, this->pos_y);

        if (!this->texture.loadFromFile("../assets/elements/brick.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }
    target.draw(this->sprite);
}

Cell::Cell() {
}
