#include "../../Header Files/views/Gameplay.hpp"
#include "../../Header Files/Game.hpp"


Gameplay::Gameplay(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats)
        : mapManager(mapManager), player(player), window(window), stats(stats) {

    stats->initStats();
}

void Gameplay::handleInput() {
}

void Gameplay::update(float deltaTime, sf::Clock &gameplayClock) {
    updateMap(deltaTime);
    updateMovement(deltaTime);
    updatePlayer(deltaTime);
    updateStats(gameplayClock);
}

void Gameplay::updatePlayer(float d) {
    this->player->update(d, true);
}

void Gameplay::updateMap(float d) {
    this->mapManager.update(d);
}

void Gameplay::updateStats(sf::Clock &gameplayClock) {
    this->stats->updateStats(gameplayClock);
}

void Gameplay::updateMovement(float d) {

    this->player->lastPawnState = this->player->currentPawnState;

    bool moveLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool moveRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool jump =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool squat =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    updateJumping(d);

    this->player->currentPawnState = PawnState::idle;

    //left
    if (moveLeft) {
        if (this->player->direction == Direction::right) {
            this->player->direction = Direction::left;
        }
        if (player->lastPawnState != PawnState::squat) {
            this->player->currentPawnState = PawnState::run;
        }
        if (squat) {
            this->player->currentPawnState = PawnState::squat;
        }

        float collisionHeightOffset = (player->currentPawnState == PawnState::squat) ? player->height / 2 : 0.0f;

        if (!checkCollisionWithCells(this->player->pos_x - this->player->movementSpeed * d,
                                     this->player->pos_y - collisionHeightOffset)) {
            if (player->pos_x <= +player->width) {
                player->pos_x = player->width;
            } else {
                this->player->pos_x -= this->player->movementSpeed * d;
            }
        }
    }

    //right
    if (moveRight) {
        if (this->player->direction == Direction::left) {
            this->player->direction = Direction::right;
        }
        if (player->lastPawnState != PawnState::squat) {
            this->player->currentPawnState = PawnState::run;
        }
        if (squat) {
            this->player->currentPawnState = PawnState::squat;
        }

        float collisionHeightOffset = (player->currentPawnState == PawnState::squat) ? player->height / 2 : 0.0f;

        if (!checkCollisionWithCells(this->player->pos_x + this->player->movementSpeed * d,
                                     this->player->pos_y - collisionHeightOffset)) {
            if (this->player->pos_x < (Game::width / 2)) {
                this->player->pos_x += this->player->movementSpeed * d;
            } else {
                mapManager.scrollMap(d);
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

        if (checkCollisionWithCells(this->player->pos_x, this->player->pos_y - 24.f + 16.f - player->jumpHeight)) {
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
        this->player->jumpHeight = 0.0f;
        this->player->jumpDistance = 0.0f;

        if (!checkCollisionWithCells(this->player->pos_x, this->player->pos_y + gravity * d)) {
            this->player->pos_y += gravity * d;
            this->player->isFalling = true;
        } else {
            this->player->isFalling = false;
        }

        if (this->player->pos_y > Game::height - player->height) {
            //todo kill player
        };
    }
}

bool Gameplay::checkCollisionWithCells(float x, float y) {

    for (auto &column: mapManager.currentMap->mapData) {
        for (auto &cell: column) {

            if (cell.cellType == CellType::platform || cell.cellType == CellType::randomReward ||
                cell.cellType == CellType::emptyRandomReward || cell.cellType == CellType::fire ||
                cell.cellType == CellType::pointsReward || cell.cellType == CellType::powerReward ||
                cell.cellType == CellType::enemyReward || cell.cellType == CellType::heartReward
                || cell.cellType == CellType::removeHeartReward) {

                bool collisionX = x + player->width > cell.pos_x
                                  && cell.pos_x + cell.width > x;

                bool collisionY;
                if (player->currentPawnState == PawnState::squat) {
                    collisionY = y + player->height > cell.pos_y && y < cell.pos_y;
                } else {
                    collisionY = y + player->height > cell.pos_y &&
                                 cell.pos_y + cell.height > y - 16;
                }

                if (collisionX && collisionY) {
                    if (player->isFalling && y + player->height > cell.pos_y + cell.height &&
                        y < cell.pos_y + cell.height) {
                        player->pos_y = cell.pos_y - player->height - 16;
                        player->isFalling = false;
                    }

                    switch (cell.cellType) {
                        case CellType::randomReward:
                            cell.changeCellType(cell.getRandomReward());
                            return true;
                        case CellType::powerReward:
                            stats->addPower(3);
                            cell.changeCellType(CellType::emptyRandomReward);
                            break;
                        case CellType::pointsReward:
                            stats->addPoints(100);
                            cell.changeCellType(CellType::emptyRandomReward);
                            break;
                        case CellType::heartReward:
                            stats->addLive();
                            cell.changeCellType(CellType::emptyRandomReward);
                            break;
                        case CellType::removeHeartReward:
                            stats->removeLive(0.5);
                            cell.changeCellType(CellType::emptyRandomReward);
                            break;
                        case CellType::enemyReward:
                            // todo enemy random generate
                            cell.changeCellType(CellType::emptyRandomReward);
                            break;
                        case CellType::fire:
                            this->player->currentPawnState = PawnState::die;
                            break;

                        default:
                            break;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void Gameplay::render() {
    renderMap();
    renderStats();
    renderPlayer();
}

void Gameplay::renderPlayer() {
    this->player->render(this->window);
}

void Gameplay::renderMap() {
    this->mapManager.render(this->window);
}

void Gameplay::renderStats() {
    this->stats->render(this->window);
}