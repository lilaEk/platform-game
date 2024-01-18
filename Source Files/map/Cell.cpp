#include "../../Header Files/map/Cell.hpp"

Cell::Cell(CellType type) : Entity() {
    width = cellSize;
    height = cellSize;

    cellType = type;
}

Cell::Cell() { }

void Cell::render(sf::RenderTarget &target) {

    if (cellType == CellType::empty) {
        return;
    }
    scale = 1.f;
    sprite.setScale(scale, scale);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(pos_x, pos_y);

    if (cellType == CellType::platform) {
        if (!texture.loadFromFile("../assets/blocks/brick.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    } else if (cellType == CellType::randomReward) {
        if (!texture.loadFromFile("../assets/blocks/questionMarkBlock.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    } else if (cellType == CellType::emptyRandomReward) {
        if (!texture.loadFromFile("../assets/blocks/questionMarkEmpty.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    } else if (cellType == CellType::powerReward) {
        if (!texture.loadFromFile("../assets/blocks/powerReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }else if (cellType == CellType::pointsReward) {
        if (!texture.loadFromFile("../assets/blocks/pointsReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }else if (cellType == CellType::enemyReward) {
        if (!texture.loadFromFile("../assets/blocks/enemyReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }else if (cellType == CellType::heartReward) {
        if (!texture.loadFromFile("../assets/blocks/heartReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }else if (cellType == CellType::removeHeartReward) {
        if (!texture.loadFromFile("../assets/blocks/removeHeartReward.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }else if (cellType == CellType::fire) {
        if (!texture.loadFromFile("../assets/blocks/fire.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    } else if (cellType == CellType::debbug) {
        if (!texture.loadFromFile("../assets/blocks/debbug.png")) {
            std::cerr << "ERROR: Could not load platform texture from file\n";
        } else {
            sprite.setTexture(texture);
        }
    }
    target.draw(sprite);
}

void Cell::changeCellType(CellType cellType){
    this->cellType = cellType;
}

CellType Cell::getRandomReward() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int random = std::rand() % 5 + 1;

    switch (random) {
        case 1:
            return CellType::pointsReward;
        case 2:
            return CellType::powerReward;
        case 3:
            return CellType::enemyReward;
        case 4:
            return CellType::heartReward;
        case 5:
            return CellType::removeHeartReward;
        default:
            return CellType::randomReward;
    }
}
