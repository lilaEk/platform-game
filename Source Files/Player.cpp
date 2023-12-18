#include "../Headers/Game.hpp"
#include "fmt/core.h"
//#include "iostream"

Player::Player() : Pawn() {
    this->initPlayer();
    this->direction = Direction::right;
}

Player::~Player() = default;

void Player::initPlayer() {
    this->currentPawnState = PawnState::idle;
    this->sprite.setScale(scale,scale);
}

void Player::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
    this->sprite.setPosition(this->position_x, this->position_y);
    target.draw(this->sprite);
//    std::cout << "position_x: " << this->sprite.getPosition().x << std::endl;
}

void Player::update(float currentTime) {
    this->updateMovement(currentTime);
    this->updateAnimations(currentTime);
}

void Player::updateMovement(float currentTime) {

    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
//        this->position_x -= movement_speed * currentTime;
        this->position_x -= 8.F;
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
//        this->position_x += movement_speed * currentTime;
        this->position_x += 8.F;
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
        if (this->position_y < 0.f) {
            this->position_y = 0.f;
        };
        this->currentPawnState = PawnState::jump;
    }
        //roll / squat - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->position_y += 20.F;
        if (this->position_y > 500.f) {
            this->position_y = 500.f;
        };
        this->currentPawnState = PawnState::roll;
    }
        //directAttack - k - todo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        this->currentPawnState = PawnState::directAttack;
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
            this->sprite = run.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
        case ::jump:
            this->sprite = jump.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
//        case jumpAttack:
//            break;
        case ::die:
            this->sprite = death.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
//        case roll:
//            break;
//        case squat:
//            break;
//        case happy:
//            break;
        case ::push:
            this->sprite = push.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
//        case lift:
//            break;
        case ::hurt:
            this->sprite = hurt.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
//        case fly:
//            break;
//        case ::pic:
//            break;
        case ::directAttack:
            this->sprite = directAttack.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
        case ::directDoubleAttack:
            this->sprite = directDoubleAttack.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
        case ::throwAttack:
            this->sprite = throwAttack.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
        default: //idle
            this->sprite = idle.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
            break;
    }
}
