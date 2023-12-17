#include "../Headers/Game.hpp"
#include "fmt/core.h"
#include "iostream"

Player::Player() : Pawn() {
    this->initSprite();
    this->direction = Direction::right;
}

Player::~Player() = default;

void Player::initSprite() {
    this->currentPawnState = PawnState::idle;
    this->lastDirection=Direction::right;
}

void Player::render(sf::RenderTarget &target) {
    this->sprite.setPosition(this->position_x, this->position_y);
//    Animation::checkDirection(this->sprite,this->direction,this->scale);
    std::cout << "position_x: " << this->sprite.getPosition().x << std::endl;
    target.draw(this->sprite);
}

void Player::update(float deltaTime) {
    this->updateMovement(deltaTime);
    this->updateAnimations(deltaTime);
}

void Player::updateMovement(float deltaTime) {
    float movement_speed = 8000000.f;

    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->position_x -= movement_speed * deltaTime;
        if (this->position_x < 0) { this->position_x = 0; };
        this->currentPawnState = PawnState::run;
        if (lastDirection==Direction::right) {
            this->direction = Direction::left;
            Animation::checkDirection(this->sprite, this->direction, this->scale);
        }
    }
        //right movement
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
            or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            this->position_x += movement_speed * deltaTime;
            this->currentPawnState = PawnState::run;
            if (lastDirection==Direction::left){
                std::cout<<"zmiana kierunku na lewo"<<std::endl;
                this->direction = Direction::right;
                Animation::checkDirection(this->sprite,this->direction,this->scale);
            }
        }
            //jump later
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                 or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            this->sprite.move(0.f, -movement_speed);
            this->currentPawnState = PawnState::run;
        }
            //down - do wyrzucenia
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
                 or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

            this->sprite.move(0.f, movement_speed);
            this->currentPawnState = PawnState::run;
        }
            //brak ruchu
        else {
            this->currentPawnState = PawnState::idle;
        }
    }
}

void Player::updateAnimations(float deltaTime) {
    switch (this->currentPawnState) {
        case PawnState::run:
            this->sprite = run.getCurrentAnimImg(deltaTime, this->width, this->height);
            break;
        default:
            this->sprite = idle.getCurrentAnimImg(deltaTime, this->width, this->height);
            break;
    }
}