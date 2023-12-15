#include "../Headers/Game.hpp"

Player::Player() : Pawn(),
    Animation("../assets/Pink_Monster/Pink_Monster_Idle.png",4),
    deltaTime(0.0f){
    //inits
    this->initTexture("../assets/Pink_Monster/Pink_Monster_Idle.png");
    this->initSprite();
}

Player::~Player() = default;

void Player::initSprite() {
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(64, 0, 32, 32);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(2.5f, 2.5f);
}

void Player::initTexture(const std::string& texturePath) {
    if (!this->textureSheet.loadFromFile("../assets/Pink_Monster/Pink_Monster_Idle.png")) {
        std::cout << "ERROR::PLAYER::Could not load the player\n";
    }
}

void Player::initAnimations() { }

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

void Player::update() {
    this->updateMovement();
    this->updateAnimations();

//    Animation::getCurrentAnimImg()
}

void Player::updateMovement() {
    //left movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->Animation::sprite.move(-05.F, 0.f);
    }
        //right movement
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->Animation::sprite.move(05.f, 0.f);
    }
        //jump later
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->Animation::sprite.move(0.f, -05.f);
    }
        //down - do wyrzucenia
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->Animation::sprite.move(0.f, 05.f);
    }
}

void Player::updateAnimations() {
    Animation::getCurrentAnimImg(deltaTime, width, height);
}
