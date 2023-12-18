#include "../Header Files/Game.hpp"
#include "fmt/core.h"
//#include "iostream"

Player::Player() : Pawn() {
    this->initPlayer();
    this->direction = Direction::right;
}

Player::~Player() = default;

void Player::initPlayer() {
    this->currentPawnState = PawnState::idle;
    this->sprite.setScale(scale, scale);
}

void Player::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
    this->sprite.setPosition(this->position_x, this->position_y);
    target.draw(this->sprite);
}

void Player::update(float currentTime) {
    this->updateMovement(currentTime);
    this->updateAnimations(currentTime);
}

void Player::updateMovement(float currentTime) {
    this->lastPawnState = this->currentPawnState;
    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {

        this->position_x -= movement_speed * currentTime;

        if (this->position_x < 0 + width) {
            this->position_x = 0 + width;
        };
        this->currentPawnState = PawnState::run;
        if (this->direction == Direction::right) {
            this->direction = Direction::left;
        }
    }
        //right movement
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->position_x += movement_speed * currentTime;

        if (this->position_x > 1200 - width) {
            this->position_x = 1200 - width;
        };
        this->currentPawnState = PawnState::run;
        if (this->direction == Direction::left) {
            this->direction = Direction::right;
        }
    }
        //jump - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->position_y -= 20.F;
        if (this->position_y < 50.f) {
            this->position_y = 50.f;
        };
        this->currentPawnState = PawnState::jump;
    }
        //roll / squat - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->position_y += 20.F;
        if (this->position_y > 450.f) {
            this->position_y = 450.f;
        };
        this->currentPawnState = PawnState::roll;
    }
        //directDoubleAttack - k - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        this->currentPawnState = PawnState::directDoubleAttack;
    }
        //throwAtack - l - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        this->currentPawnState = PawnState::throwAttack;
    }
        //brak ruchu
    else {
        this->currentPawnState = PawnState::idle;
    }
}

void Player::updateAnimations(float deltaTime) {

    switch (this->currentPawnState) {
        case PawnState::run:
            this->sprite = run.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                 this->scale, PawnState::run);
            break;
        case ::PawnState::jump:
            this->sprite = jump.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::jump);
            break;
        case ::PawnState::die:
            this->sprite = death.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                   PawnState::die);
            break;
//        case roll:
//            break;
//        case squat:
//            break;
//        case happy:
//            break;
//        case ::PawnState::push:
//            this->sprite = push.getCurrentAnimImg(this->width, this->height, this->direction, this->scale, PawnState::push);
//            break;
//        case lift:
//            break;
        case ::PawnState::hurt:
            this->sprite = hurt.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::hurt);
            break;
//        case fly:
//            break;
//        case ::pic:
//            break;
//        case ::directAttack:
//            this->sprite = directAttack.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
//            break;
        case ::PawnState::directDoubleAttack:
            this->sprite = directDoubleAttack.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                                this->scale, PawnState::directDoubleAttack);
            break;
        case ::PawnState::throwAttack:
            this->sprite = throwAttack.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                         this->scale, PawnState::throwAttack);
            break;
        default: //idle
            this->sprite = idle.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::idle);
            break;
    }
}
