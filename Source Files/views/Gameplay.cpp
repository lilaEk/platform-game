#include "../../Header Files/views/Gameplay.hpp"
#include "../../Header Files/Game.hpp"


Gameplay::Gameplay(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats, Enemy *enemy)
        : mapManager(mapManager), player(player), window(window), stats(stats), enemy(enemy) {

    stats->initStats();
    enemy->initPawn();

}

void Gameplay::handleInput() {
}

void Gameplay::update(float deltaTime) {
    updateMap(deltaTime);
    updateMovement(deltaTime);
    updatePlayer(deltaTime);
    updateEnemies(deltaTime);
}

void Gameplay::updatePlayer(float d) {
    player->update(d, true);
}

void Gameplay::updateEnemies(float d) {
    enemy->update(d, true);
    handleEnemyCollisions();

}

void Gameplay::updateMap(float d) {
    mapManager.update(*enemy);
}

void Gameplay::updateMovement(float d) {

    player->lastPawnState = player->currentPawnState;

    bool moveLeft =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool moveRight =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool jump =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool squat =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    updateJumping(d);

    player->currentPawnState = PawnState::idle;

    //left
    if (moveLeft) {
        if (player->direction == Direction::right) { player->direction = Direction::left; }
        if (player->lastPawnState != PawnState::squat) { player->currentPawnState = PawnState::run; }
        if (squat) { player->currentPawnState = PawnState::squat; }

        float collisionHeightOffset = (player->currentPawnState == PawnState::squat) ? player->height / 2 : 0.0f;

        if (!checkCollisionWithCells(player->pos_x - player->movementSpeed * d,
                                     player->pos_y - collisionHeightOffset, true)) {
            if (player->pos_x <= +player->width) {
                player->pos_x = player->width;
            } else { player->pos_x -= player->movementSpeed * d; }
        }
    }

    //right
    if (moveRight) {
        if (player->direction == Direction::left) {
            player->direction = Direction::right;
        }
        if (player->lastPawnState != PawnState::squat) {
            player->currentPawnState = PawnState::run;
        }
        if (squat) {
            player->currentPawnState = PawnState::squat;
        }

        float collisionHeightOffset = (player->currentPawnState == PawnState::squat) ? player->height / 2 : 0.0f;

        if (!checkCollisionWithCells(player->pos_x + player->movementSpeed * d,
                                     player->pos_y - collisionHeightOffset, true)) {
            if (player->pos_x < (Game::width / 2)) {
                player->pos_x += player->movementSpeed * d;
            } else {
                mapManager.scrollMap(d, *enemy);
            }
        }
    }

    //jump
    if (jump) {
        if (!player->isJumping && !player->isFalling) {
            player->currentPawnState = PawnState::jump;
            player->isJumping = true;
        }
    }

    //squat
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

        player->currentPawnState = PawnState::squat;
    }

    //attack
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        player->currentPawnState = PawnState::directDoubleAttack;
    }

    //throw
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        player->currentPawnState = PawnState::throwAttack;
    }

}

void Gameplay::updateJumping(float d) {
    if (player->isJumping) {

        player->jumpHeight = jumpSpeed * d;

        if (checkCollisionWithCells(player->pos_x, player->pos_y - 24.f + 16.f - player->jumpHeight, true)) {
            player->currentPawnState = PawnState::idle;
            player->isJumping = false;
            player->isFalling = true;
            player->jumpHeight = 0.0f;
            return;
        }

        if (player->pos_y < 60.f) {
            player->pos_y = 60.f;
            player->isJumping = false;
            player->isFalling = true;
            player->jumpHeight = 0.0f;
            player->currentPawnState = PawnState::idle;
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player->currentPawnState = PawnState::idle;
            player->jumpHeight = 0;
            player->isJumping = false;
            player->isFalling = true;
            return;
        }

        player->pos_y -= player->jumpHeight;
        player->jumpDistance += player->jumpHeight;

        if (player->jumpDistance >= 48.f * 4) {
            player->jumpHeight = 0.0f;
            player->jumpDistance = 0.0f;
            player->currentPawnState = PawnState::idle;
            player->isJumping = false;
            player->isFalling = true;
            return;
        }

    } else {
        player->jumpHeight = 0.0f;
        player->jumpDistance = 0.0f;

        if (!checkCollisionWithCells(player->pos_x, player->pos_y + gravity * d, true)) {
            player->pos_y += gravity * d;
            player->isFalling = true;
        } else {
            player->isFalling = false;
        }

        if (player->pos_y > Game::height - player->height) {
            stats->removeLive(5);
        };
    }
}

bool Gameplay::checkCollisionWithCells(float x, float y, bool ifPlayer) {

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

                    if (ifPlayer) {
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
                                if (rand() % 5 + 1 == 5) {
                                    break;
                                }
                                cell.changeCellType(CellType::emptyRandomReward);
                                break;
                            case CellType::heartReward:
                                stats->addLive();
                                cell.changeCellType(CellType::emptyRandomReward);
                                break;
                            case CellType::removeHeartReward:
                                playerHurt(0.5);
                                cell.changeCellType(CellType::emptyRandomReward);
                                break;
                            case CellType::enemyReward:
                                enemy->initForestBoss(cell.pos_x + cell.cellSize * 3);
                                cell.changeCellType(CellType::emptyRandomReward);
                                break;
                            case CellType::fire:
                                stats->removeLive(5);
                                break;

                            default:
                                break;
                        }
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
    renderEnemies();
}

void Gameplay::renderPlayer() {
    player->render(window);
}

void Gameplay::renderEnemies() {
    enemy->render(window);
}

void Gameplay::renderMap() {
    mapManager.render(window);
}

void Gameplay::renderStats() {
    stats->render(window);
}

void Gameplay::handleEnemyCollisions() {
    for (auto &enemy: enemy->allEnemies) {

        if (checkCollisionWithWalls(*enemy)) {
            enemy->direction = (enemy->direction == Direction::left) ? Direction::right : Direction::left;
            enemy->distance = 0.f;
        }

        if (checkCollisionWithPlayer(*enemy, *player)) {
            enemy->currentPawnState = PawnState::directAttack;
            if (enemy->type==EnemyType::snake) {
                playerHurt(0.5);
            }else if (enemy->type==EnemyType::forest_boss) {
                playerHurt(1);
            }

        } else {
            enemy->currentPawnState = PawnState::run;
        }
    }
}

bool Gameplay::checkCollisionWithWalls(Enemy &enemy) {

    for (auto &column: mapManager.currentMap->mapData) {
        for (auto &cell: column) {
            if (cell.cellType == CellType::platform || cell.cellType == CellType::platform) {
                bool collisionX = enemy.pos_x + enemy.width > cell.pos_x &&
                                  cell.pos_x + cell.width > enemy.pos_x;

                bool collisionY = enemy.pos_y + enemy.height > cell.pos_y &&
                                  cell.pos_y + cell.height > enemy.pos_y;

                if (collisionX && collisionY) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Gameplay::checkCollisionWithPit(Enemy &enemy) {
    float feetPosition = enemy.pos_y + enemy.height;
    bool isAboveGround = !checkCollisionWithCells(enemy.pos_x, feetPosition, false);

    return isAboveGround;
}

bool Gameplay::checkCollisionWithPlayer(Enemy &enemy, Player &player) {
    bool collisionX = enemy.pos_x + enemy.width > player.pos_x &&
                      player.pos_x + player.width > enemy.pos_x;

    bool collisionY = enemy.pos_y + enemy.height > player.pos_y &&
                      player.pos_y + player.height > enemy.pos_y;

    return collisionX && collisionY;
}

void Gameplay::playerHurt(int loss) {
    player->currentPawnState = PawnState::hurt;
    stats->removeLive(0.5);
    player->hurt.lastPlayedFrameIndex = 0;
}
