#include "../../Header Files/views/Gameplay.hpp"
#include "../../Header Files/Game.hpp"


Gameplay::Gameplay(MapManager *mapManager, Player *player, sf::RenderWindow &window)
        : mapManager(mapManager), player(player), window(window) {

}

void Gameplay::handleInput() {
}

void Gameplay::update(float deltaTime) {
    updateMap(deltaTime);
    updateMovement(deltaTime);
    updatePlayer(deltaTime);
}

void Gameplay::updatePlayer(float d) {
    this->player->update(d, true);
}

void Gameplay::updateMap(float d) {
    this->mapManager->update(d);
}

void Gameplay::render() {
    renderMap();
    renderPlayer();
}

void Gameplay::renderPlayer() {
    this->player->render(this->window);
}

void Gameplay::renderMap() {
    this->mapManager->render(this->window);
}

void Gameplay::updateMovement(float currentTime) {

    this->player->lastPawnState = this->player->currentPawnState;

    bool moveLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool moveRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    // Lewo
    if (moveLeft) {
        if (this->player->direction == Direction::right) {
            this->player->direction = Direction::left;
        }
        this->player->currentPawnState = PawnState::run;

        if (checkCollisionWithCells(this->player->pos_x - this->player->movement_speed * currentTime,
                                    this->player->pos_y)) {
            return;
        } else if (player->pos_x <=  + player->width) {
            player->pos_x = player->width;
        } else {
            this->player->pos_x -= this->player->movement_speed * currentTime;
        }
        std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;

    }
        // Prawo
    else if (moveRight) {
        if (this->player->direction == Direction::left) {
            this->player->direction = Direction::right;
        }
        this->player->currentPawnState = PawnState::run;

//        if (checkCollision(this->player->movement_speed * currentTime, 0, true)) {
        if (checkCollisionWithCells(this->player->pos_x + this->player->movement_speed * currentTime,
                                    this->player->pos_y)) {
            return;
        } else if (this->player->pos_x < (Game::width / 2)) {
            this->player->pos_x += this->player->movement_speed * currentTime;
        } else {
            mapManager->scrollMap(currentTime);
        }
        std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;

    }

        //jump
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {

        this->player->currentPawnState = PawnState::jump;

        if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y - 10.f)) {
            return;
        }
        this->player->pos_y -= this->player->movement_speed*2 * currentTime;
        if (this->player->pos_y < 30.f) {
            this->player->pos_y = 30.f;
        };
        std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;


        //squat
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

        this->player->currentPawnState = PawnState::squat;

        if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y + 20.f)) {
            return;
        }
        this->player->pos_y += this->player->movement_speed*2 * currentTime;
        if (this->player->pos_y > Game::height-48*2.5) {
//kill player
        };
        std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;


        //attack
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        this->player->currentPawnState = PawnState::directDoubleAttack;

        //throw
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        this->player->currentPawnState = PawnState::throwAttack;

    } else {
        this->player->currentPawnState = PawnState::idle;
    }
}

bool Gameplay::checkCollisionWithCells(float x, float y) {

    for (auto &column: mapManager->currentMap->mapData) {
        for (auto &cell: column) {

            if (cell.cellType == CellType::platform || cell.cellType == CellType::randomReward|| cell.cellType == CellType::debbug) {

                bool collisionX = x + player->width > cell.pos_x
                                  && cell.pos_x + cell.width > x;

                bool collisionY = y + player->height > cell.pos_y &&
                                  cell.pos_y + cell.height > y;

                if (collisionX && collisionY) {
                    cell.changeCellType(CellType::debbug);

                    std::cout << "Kolizja z komorka: (" << cell.pos_x << "," << cell.pos_y
                              <<")("<<cell.pos_x+cell.width<<","<<cell.pos_y+cell.height<< ").\n"
                              <<"Pozycja gracza: (" << player->pos_x << "," << player->pos_y << ")"
                            <<")("<<player->pos_x+player->width<<","<<player->pos_y+player->height<< ").\n"
                            << std::endl;

                    std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;

                    return true;
                }
            }
        }
    }
    return false;
}