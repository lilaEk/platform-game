#include "../Headers/Game.hpp"
#include "fmt/core.h"
#include "iostream"

Player::Player() : Pawn() {
    this->initPlayerState();
    this->direction = Direction::right;
}

Player::~Player() = default;

void Player::initPlayerState() {
    this->currentPawnState = PawnState::idle;
}

void Player::render(sf::RenderTarget &target) {

    this->sprite.setPosition(this->position_x, this->position_y);
    target.draw(this->sprite);

    std::cout << "position_x: " << this->sprite.getPosition().x << std::endl;
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
        if (this->position_x < 0+width) {
            this->position_x = 0+width; };
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
        if (this->position_x > 1200-width) {
            this->position_x = 1200-width; };
        this->currentPawnState = PawnState::run;
        if (this->direction == Direction::left) {
            this->direction = Direction::right;
        }
    }

/*
//            //jump later
//        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
//                 or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
//            this->sprite.move(0.f, -movement_speed);
//            this->currentPawnState = PawnState::run;
//        }
//            //down - do wyrzucenia
//        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
//                 or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
//
//            this->sprite.move(0.f, movement_speed);
//            this->currentPawnState = PawnState::run;
//        }
 */

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
            break;
//        case jumpAttack:
//            break;
        case ::die:
            break;
//        case roll:
//            break;
//        case squat:
//            break;
//        case happy:
//            break;
        case ::push:
            break;
//        case lift:
//            break;
        case ::hurt:
            break;
//        case fly:
//            break;
//        case ::pic:
//            break;
        case ::directAttack:
            break;
        case ::directDoubleAttack:
            break;
        case ::throwAttack:
            break;
        default: //idle
            this->sprite = idle.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);

            break;
    }
}
