#include "../Header Files/Animation.hpp"


Animation::Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *lastPawnState) :
        assetPath(assetPath), framesNumber(framesNumber), lastPawnState(lastPawnState) {
    this->scale = 1.0F;
    if (!texture.loadFromFile(assetPath)) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    this->sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);
}

Animation &Animation::operator=(const Animation &other) {

    const_cast<std::string &>(this->assetPath) = std::move(other.assetPath);
    this->framesNumber = other.framesNumber;
    this->scale = other.scale;

    this->texture = sf::Texture(other.texture);
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setScale(scale, scale);

    this->elapsed = other.elapsed;
    this->framesNumber = other.framesNumber;

    this->lastPawnState = other.lastPawnState;

    return *this;
}

Animation::~Animation() = default;

void Animation::restartAnim() {
    this->lastPlayedFrameIndex = 0;
}

sf::Sprite
Animation::getCurrentAnimImg(float deltaTime, int w, int h, Direction direction, float scale, PawnState newPawnState) {
    if (*lastPawnState != newPawnState) {
//        std::cout << "Current State: " << *lastPawnState << std::endl;
//        std::cout << "New State: " << newPawnState << std::endl << std::endl;
        *lastPawnState = newPawnState;
        restartAnim();
    }

    this->elapsed += deltaTime;
    if (elapsed >= frameDuration) {
        lastPlayedFrameIndex++;
        if (lastPlayedFrameIndex >= framesNumber) {
            restartAnim();
        }
        elapsed = 0;
    }

    newDirectionAndScale(this->sprite, direction, scale);
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