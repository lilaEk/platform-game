#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    this->width = cellSize;
    this->height = cellSize;

    this->cellType = type;
}

Cell::Cell() { }

//void Cell::loadTexture(CellType type) {
//    switch (type) {
//        case CellType::platform:
//            texture.loadFromFile("../assets/blocks/brick.png");
//            break;
//        case CellType::randomReward:
//            texture.loadFromFile("../assets/blocks/questionMarkBlock.png");
//            break;
//        case CellType::emptyRandomReward:
//            texture.loadFromFile("../assets/blocks/questionMarkEmpty.png");
//            break;
//        case CellType::powerReward:
//            texture.loadFromFile("../assets/blocks/powerReward.png");
//            break;
//        case CellType::pointsReward:
//            texture.loadFromFile("../assets/blocks/pointsReward.png");
//            break;
//        case CellType::heartReward:
//            texture.loadFromFile("../assets/blocks/heartReward.png");
//            break;
//        case CellType::enemyReward:
//            texture.loadFromFile("../assets/blocks/enemyReward.png");
//            break;
//        case CellType::fire:
//            texture.loadFromFile("../assets/blocks/fire.png");
//            break;
//        case CellType::debbug:
//            texture.loadFromFile("../assets/blocks/debbug.png");
//            break;
//        default:
//            break;
//    }
//}

void Cell::render(sf::RenderTarget &target) {
//    if (this->cellType == CellType::empty) {
//        return;
//    }
//
//    if (texture.getSize().x == 0) {
//        loadTexture(cellType);
//    }
//
//    this->scale = 1.f;
//    this->sprite.setScale(this->scale, this->scale);
//    this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
//    this->sprite.setPosition(this->pos_x, this->pos_y);
//
//    this->sprite.setTexture(this->texture);
//    target.draw(this->sprite);
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
    } else if (this->cellType == CellType::emptyRandomReward) {
        if (!this->texture.loadFromFile("../assets/blocks/questionMarkEmpty.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    } else if (this->cellType == CellType::powerReward) {
        if (!this->texture.loadFromFile("../assets/blocks/powerReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }else if (this->cellType == CellType::pointsReward) {
        if (!this->texture.loadFromFile("../assets/blocks/pointsReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }else if (this->cellType == CellType::enemyReward) {
        if (!this->texture.loadFromFile("../assets/blocks/enemyReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }else if (this->cellType == CellType::heartReward) {
        if (!this->texture.loadFromFile("../assets/blocks/heartReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            this->sprite.setTexture(this->texture);
        }
    }else if (this->cellType == CellType::fire) {
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
