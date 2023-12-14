#include "../Headers/Game.hpp"

void Player::initSprite() {
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(64, 0, 32, 32);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.5f, 2.5f);
}

void Player::initTexture() {
    if (!this->textureSheet.loadFromFile("../assets/Pink_Monster/Pink_Monster_Idle.png")) {
        std::cout << "ERROR::PLAYER::Could not load the player\n";
    }
}

void Player::initAnimations() {

}

Player::Player() {
    //inits
    this->initTexture();
    this->initSprite();
}

Player::~Player() = default;

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

void Player::update() {
    this->updateMovement();
}

void Player::updateMovement() {
    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->sprite.move(-05.F, 0.f);
    }
        //right movement
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->sprite.move(05.f, 0.f);
    }
        //jump later
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->sprite.move(0.f, -05.f);
    }
        //down - do wyrzucenia
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->sprite.move(0.f, 05.f);
    }
}

void Player::updateAnimations() {

}
