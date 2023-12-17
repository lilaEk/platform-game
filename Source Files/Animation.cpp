#include "../Headers/Animation.hpp"

Animation::Animation(const std::string &assetPath, int framesNumber, float scale) :
        assetPath(assetPath), framesNumber(framesNumber), scale(scale) {
    if (!texture.loadFromFile(assetPath)) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    this->sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);

}

Animation::Animation(const std::string &assetPath, int framesNumber) :
        assetPath(assetPath), framesNumber(framesNumber) {
    this->scale = 1.0F;
    if (!texture.loadFromFile(assetPath)) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    this->sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);

}

Animation::~Animation() {}

int Animation::restartAnim() {
    return this->lastPlayedFrameIndex = 0;
}

sf::Sprite Animation::getCurrentAnimImg(long deltaT, int w, int h) {

    this->elapsed += deltaT;
    if (this->elapsed >= this->frameDuration) {
        this->lastPlayedFrameIndex++;
        if (this->lastPlayedFrameIndex >= this->framesNumber) {
            this->lastPlayedFrameIndex = 0;
        }
        this->elapsed = 0;
    }

    if (this->lastPlayedFrameIndex == this->framesNumber - 1) {
        restartAnim();
        sf::IntRect currentFrame = sf::IntRect((this->lastPlayedFrameIndex) * w, 0, w, h);
        sprite.setTextureRect(currentFrame);
        return sprite;
    }
    this->lastPlayedFrameIndex += 1;
    sf::IntRect currentFrame = sf::IntRect(
            (this->lastPlayedFrameIndex) * w, 0, w, h);
    sprite.setTextureRect(currentFrame);

    return sprite;
}

void Animation::checkDirection(sf::Sprite &sprite, Direction direction, float scale) {

    if (direction == Direction::left) {
        sprite.setScale(-scale, scale);
    }
    if (direction == Direction::right) {
        sprite.setScale(scale, scale);
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    sf::Vector2f oldPosition = sprite.getPosition();

    if (direction == Direction::left) {
        sprite.setPosition(oldPosition.x + bounds.width * scale, oldPosition.y);
    }
    if (direction == Direction::right) {
        sprite.setPosition(oldPosition.x - bounds.width * scale, oldPosition.y);
    }
}
