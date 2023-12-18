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

Animation::~Animation() = default;

int Animation::restartAnim() {
    return this->lastPlayedFrameIndex = 0;
}

sf::Sprite Animation::getCurrentAnimImg(int w, int h, Direction direction, float scale) {

    if (this->lastDirectionToCompare != direction) {
        newDirection(this->sprite, direction, scale);
        lastDirectionToCompare = direction;
    }

    if (this->lastPlayedFrameIndex >= this->framesNumber - 1) {
        restartAnim();
        return getSprite(w, h);
    }
    this->lastPlayedFrameIndex += 1;
    return getSprite(w, h);

}

sf::Sprite Animation::getSprite(int w, int h) {
    sf::IntRect currentFrame = sf::IntRect((lastPlayedFrameIndex) * w, 0, w, h);
    sprite.setTextureRect(currentFrame);
    return sprite;
}

void Animation::newDirection(sf::Sprite &sprite, Direction direction, float scale) {

    sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);

    if (direction == Direction::left) {
        sprite.setScale(-scale, scale);
    } else {
        sprite.setScale(scale, scale);
    }
}
