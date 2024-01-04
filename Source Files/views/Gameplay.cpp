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

    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {

        this->player->pos_x -= this->player->movement_speed * currentTime;

        if (this->player->pos_x < 0 + this->player->width) {
            this->player->pos_x = 0 + this->player->width;
        };
        this->player->currentPawnState = PawnState::run;
        if (this->player->direction == Direction::right) {
            this->player->direction = Direction::left;
        }
    }
        //right movement
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {

        if (this->player->pos_x<(Game::width/2)) {
            this->player->pos_x += this->player->movement_speed * currentTime;

            if (this->player->pos_x > Game::width - this->player->width) {
                this->player->pos_x = Game::width - this->player->width;
            };
        } else {
            mapManager->scrollMap(currentTime);
        }

        this->player->currentPawnState = PawnState::run;
        if (this->player->direction == Direction::left) {
            this->player->direction = Direction::right;
        }
    }
        //jump - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->player->pos_y -= 10.F;
        if (this->player->pos_y < 30.f) {
            this->player->pos_y = 30.f;
        };
        this->player->currentPawnState = PawnState::jump;
    }
        //roll / squat - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->player->pos_y += 20.F;
        if (this->player->pos_y > 500.f) {
            this->player->pos_y = 500.f;
        };
        this->player->currentPawnState = PawnState::squat;
    }
        //directDoubleAttack - k - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        this->player->currentPawnState = PawnState::directDoubleAttack;
    }
        //throwAtack - l - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        this->player->currentPawnState = PawnState::throwAttack;
    }
        //brak ruchu
    else {
        this->player->currentPawnState = PawnState::idle;
    }
}