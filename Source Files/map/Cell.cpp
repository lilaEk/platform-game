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

    switch (this->cellType) {
        case CellType::platform:
            this->texture.loadFromFile("../assets/blocks/brick.png");
            break;
        case CellType::randomReward:
            this->texture.loadFromFile("../assets/blocks/questionMarkBlock.png");
            break;
        case CellType::emptyRandomReward:
            this->texture.loadFromFile("../assets/blocks/questionMarkEmpty.png");
            break;
        case CellType::powerReward:
            this->texture.loadFromFile("../assets/blocks/powerReward.png");
            break;
        case CellType::pointsReward:
            this->texture.loadFromFile("../assets/blocks/pointsReward.png");
            break;
        case CellType::heartReward:
            this->texture.loadFromFile("../assets/blocks/heartReward.png");
            break;
        case CellType::enemyReward:
            this->texture.loadFromFile("../assets/blocks/enemyReward.png");
            break;
        case CellType::fire:
            this->texture.loadFromFile("../assets/blocks/fire.png");
            break;
        case CellType::debbug:
            this->texture.loadFromFile("../assets/blocks/debbug.png");
            break;
    }

    this->sprite.setTexture(this->texture);
    target.draw(this->sprite);
}

void Cell::changeCellType(CellType cellType){
    this->cellType = cellType;
}

CellType Cell::getRandomReward() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int random = std::rand() % 4 + 1;

    switch (random) {
        case 1:
            std::cout<<"pointReward"<<std::endl;
            return CellType::pointsReward;
        case 2:
            std::cout<<"powerReward"<<std::endl;
            return CellType::powerReward;
        case 3:
            std::cout<<"enemyReward"<<std::endl;
            return CellType::enemyReward;
        case 4:
            std::cout<<"heartReward"<<std::endl;
            return CellType::heartReward;
        default:
            return CellType::randomReward;
    }
}
