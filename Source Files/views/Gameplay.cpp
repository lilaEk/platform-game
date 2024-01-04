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

    // Sprawdź kierunek ruchu gracza
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
        if (!checkCollision(-this->player->movement_speed * currentTime, 0)) {
            return;
        } else {
            this->player->pos_x -= this->player->movement_speed * currentTime;
        }
    }
        // Prawo
    else if (moveRight) {
        if (this->player->direction == Direction::left) {
            this->player->direction = Direction::right;
        }
        this->player->currentPawnState = PawnState::run;
        if (!checkCollision(this->player->movement_speed * currentTime, 0)) {
            return;
        } else if (this->player->pos_x < (Game::width / 2)) {
            this->player->pos_x += this->player->movement_speed * currentTime;
        } else {
            mapManager->scrollMap(currentTime);
        }
    }
        // Pozostałe przypadki
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        // Skok
        this->player->pos_y -= 10.F;
        if (this->player->pos_y < 30.f) {
            this->player->pos_y = 30.f;
        };
        this->player->currentPawnState = PawnState::jump;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        // Kucanie
        this->player->pos_y += 20.F;
        if (this->player->pos_y > 48 * 10) {
            this->player->pos_y = 48 * 10;
        };
        this->player->currentPawnState = PawnState::squat;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        // Atak
        this->player->currentPawnState = PawnState::directDoubleAttack;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        // Rzut
        this->player->currentPawnState = PawnState::throwAttack;
    } else {
        // Brak ruchu
        this->player->currentPawnState = PawnState::idle;
    }
}

//    this->player->lastPawnState = this->player->currentPawnState;
//
//    //left movement
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
//        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
//
//        if (checkCollision()) {
//            this->player->pos_x -= this->player->movement_speed * currentTime;
//
//            if (this->player->pos_x < 0 + this->player->width) {
//                this->player->pos_x = 0 + this->player->width;
//            };
//            this->player->currentPawnState = PawnState::run;
//            if (this->player->direction == Direction::right) {
//                this->player->direction = Direction::left;
//            }
//        }
//    }
//        //right movement
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
//
//        if (checkCollision()) {
//            if (this->player->pos_x < (Game::width / 2)) {
//                this->player->pos_x += this->player->movement_speed * currentTime;
//
//                if (this->player->pos_x > Game::width - this->player->width) {
//                    this->player->pos_x = Game::width - this->player->width;
//                };
//            } else {
//                mapManager->scrollMap(currentTime);
//            }
//
//            this->player->currentPawnState = PawnState::run;
//            if (this->player->direction == Direction::left) {
//                this->player->direction = Direction::right;
//            }
//        }
//    }
//        //jump - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
//        if (checkCollision()) {
//            this->player->pos_y -= 10.F;
//            if (this->player->pos_y < 30.f) {
//                this->player->pos_y = 30.f;
//            };
//        }
//        this->player->currentPawnState = PawnState::jump;
//    }
//        //roll / squat - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
//        if (checkCollision()) {
//            this->player->pos_y += 20.F;
//            if (this->player->pos_y > 48 * 10) {
//                this->player->pos_y = 48 * 10;
//            };
//        }
//        this->player->currentPawnState = PawnState::squat;
//    }
//        //directDoubleAttack - k - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
//        this->player->currentPawnState = PawnState::directDoubleAttack;
//    }
//        //throwAtack - l - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
//        this->player->currentPawnState = PawnState::throwAttack;
//    }
//        //brak ruchu
//    else {
//        this->player->currentPawnState = PawnState::idle;
//    }
//}

bool Gameplay::checkCollision(float targetX, float targetY) {

    float tempPosX = this->player->pos_x + targetX;
    float tempPosY = this->player->pos_y + targetY;

    sf::FloatRect playerBounds = player->getBoundingBox();

    this->player->setPosition(tempPosX, tempPosY);

    for (auto &column: mapManager->currentMap->mapData) {
        for (auto &cell: column) {
            sf::FloatRect cellBounds = cell.getBoundingBox();

            if (playerBounds.intersects(cellBounds)) {
                if (cell.cellType == CellType::platform || cell.cellType == CellType::randomReward) {
                    return false; // Brak kolizji
                } else if (cell.cellType == CellType::empty) {
                    return true; // Kolizja z pustą komórką
                } else if (cell.cellType == CellType::fire) {
                    // Zabij gracza
                    // Możesz umieścić tutaj odpowiednią logikę obsługi kolizji z ogniem
                    return false;
                }
            }
        }
    }
    this->player->setPosition(this->player->pos_x - targetX, this->player->pos_y - targetY);

    return true;
}

