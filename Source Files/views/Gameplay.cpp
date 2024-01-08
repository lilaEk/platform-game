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

void Gameplay::updateMovement(float d) {

    this->player->lastPawnState = this->player->currentPawnState;

    bool moveLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool moveRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool jump =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    updateJumping(d);

    this->player->currentPawnState = PawnState::idle;
    //lewo
    if (moveLeft) {
        if (this->player->direction == Direction::right) {
            this->player->direction = Direction::left;
        }
        this->player->currentPawnState = PawnState::run;

        if (!checkCollisionWithCells(this->player->pos_x - this->player->movementSpeed * d,
                                     this->player->pos_y)) {
            if (player->pos_x <= +player->width) {
                player->pos_x = player->width;
            } else {
                this->player->pos_x -= this->player->movementSpeed * d;
            }
        }
    }

    //prawo
    if (moveRight) {
        if (this->player->direction == Direction::left) {
            this->player->direction = Direction::right;
        }
        this->player->currentPawnState = PawnState::run;

        if (!checkCollisionWithCells(this->player->pos_x + this->player->movementSpeed * d,
                                     this->player->pos_y)) {
            if (this->player->pos_x < (Game::width / 2)) {
                this->player->pos_x += this->player->movementSpeed * d;
            } else {
                mapManager->scrollMap(d);
            }
        }
    }

    //jump
    if (jump) {
        if (!this->player->isJumping && !this->player->isFalling) {
            this->player->currentPawnState = PawnState::jump;
            this->player->isJumping = true;
        }
    }

    //squat
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

        this->player->currentPawnState = PawnState::squat;

//        if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y + 24.f - player->height/2)) {
//            if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y + 24.f)) {
//            return;
//        }

        if (!checkCollisionWithCells(this->player->pos_x, this->player->pos_y+24.f + player->height/2)) {
            this->player->currentPawnState = PawnState::idle;
            this->player->pos_y += 24.f;
        }
    }

    //attack
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        this->player->currentPawnState = PawnState::directDoubleAttack;
    }

    //throw
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        this->player->currentPawnState = PawnState::throwAttack;
    }

}

void Gameplay::updateJumping(float d) {
    if (player->isJumping) {

        player->jumpHeight = jumpSpeed * d;

        if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y - 24.f - player->jumpHeight)) {
            this->player->currentPawnState = PawnState::idle;
            this->player->isJumping = false;
            this->player->isFalling = true;
            this->player->jumpHeight = 0.0f;
            return;
        }

        if (this->player->pos_y < 60.f) {
            this->player->pos_y = 60.f;
            this->player->isJumping = false;
            this->player->isFalling = true;
            this->player->jumpHeight = 0.0f;
            this->player->currentPawnState = PawnState::idle;
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            this->player->currentPawnState = PawnState::idle;
            this->player->jumpHeight = 0;
            player->isJumping = false;
            this->player->isFalling = true;
            return;
        }

        this->player->pos_y -= player->jumpHeight;
        player->jumpDistance += player->jumpHeight;

        if (this->player->jumpDistance >= 48.f * 4) {
            this->player->jumpHeight = 0.0f;
            this->player->jumpDistance = 0.0f;
            this->player->currentPawnState = PawnState::idle;
            player->isJumping = false;
            this->player->isFalling = true;
            return;
        }

    } else {
        if (!checkCollisionWithCells(this->player->pos_x, this->player->pos_y + gravity * d)) {
            this->player->pos_y += gravity * d;
            this->player->isFalling = true;
        } else {
            this->player->isFalling = false;
        }

        if (this->player->pos_y > Game::height - 48 * 2.5) {
            //todo kill player
        };
    }
}

bool Gameplay::checkCollisionWithCells(float x, float y) {

    for (auto &column: mapManager->currentMap->mapData) {
        for (auto &cell: column) {

            if (cell.cellType == CellType::platform || cell.cellType == CellType::randomReward ||
                cell.cellType == CellType::emptyRandomReward || cell.cellType == CellType::fire) {

                bool collisionX = x + player->width > cell.pos_x
                                  && cell.pos_x + cell.width > x;

                bool collisionY = y + player->height > cell.pos_y &&
                                 cell.pos_y + cell.height > y;

                if (collisionX && collisionY) {

                    if (cell.cellType == CellType::randomReward) {
                        cell.changeCellType(CellType::emptyRandomReward);
                    }

                    if (cell.cellType == CellType::fire) {
                        this->player->currentPawnState = PawnState::die;
                    }

//                    cell.changeCellType(CellType::debbug);
//                    std::cout << "Kolizja z komorka: (" << cell.pos_x << "," << cell.pos_y
//                              << ")(" << cell.pos_x + cell.width << "," << cell.pos_y + cell.height << ").\n"
//                              << "Pozycja gracza: (" << player->pos_x << "," << player->pos_y << ")"
//                              << ")(" << player->pos_x + player->width << "," << player->pos_y + player->height
//                              << ").\n"
//                              << std::endl;

//                    std::cout << "player: ("<<player->pos_x<<","<<player->pos_y<<")"<<std::endl;

                    return true;
                }
            }
        }
    }
    return false;
}