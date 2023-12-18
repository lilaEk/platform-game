#include "../Headers/Animation.hpp"



Animation::Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *lastPawnState) :
        assetPath(assetPath), framesNumber(framesNumber), lastPawnState(lastPawnState) {
    this->scale = 1.0F;
    if (!texture.loadFromFile(assetPath)) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    this->sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);


}

Animation::~Animation() = default;

void Animation::restartAnim() {
    this->lastPlayedFrameIndex = 0;
}

sf::Sprite Animation::getCurrentAnimImg(int w, int h, Direction direction, float scale, PawnState newPawnState) {

    if (*lastPawnState != newPawnState) {
        std::cout << "Current State: " << *lastPawnState << std::endl;
        std::cout << "New State: " << newPawnState << std::endl << std::endl;
        *lastPawnState = newPawnState;
        restartAnim();
    }

    newDirectionAndScale(this->sprite, direction, scale);

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

void Animation::newDirectionAndScale(sf::Sprite &sprite, Direction direction, float scale) {

    if (direction == Direction::left) {
        sprite.setScale(-scale, scale);
    } else {
        sprite.setScale(scale, scale);
    }
}