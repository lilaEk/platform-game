#include "../Header Files/Animation.hpp"


Animation::Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *lastPawnState) :
        assetPath(assetPath), framesNumber(framesNumber), lastPawnState(lastPawnState) {
    scale = 1.0F;
    if (!texture.loadFromFile(assetPath)) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);
}

Animation &Animation::operator=(const Animation &other) {

    const_cast<std::string &>(assetPath) = std::move(other.assetPath);
    framesNumber = other.framesNumber;
    scale = other.scale;

    texture = sf::Texture(other.texture);
    sprite = sf::Sprite(texture);
    sprite.setScale(scale, scale);

    elapsed = other.elapsed;
    framesNumber = other.framesNumber;

    lastPawnState = other.lastPawnState;

    return *this;
}

Animation::~Animation() = default;

void Animation::restartAnim() {
    lastPlayedFrameIndex = 0;
}

sf::Sprite
Animation::getCurrentAnimImg(float deltaTime, int w, int h, Direction direction, float scale, PawnState newPawnState) {
    if (*lastPawnState != newPawnState) {
        *lastPawnState = newPawnState;

        if (newPawnState==PawnState::squat){
            lastPlayedFrameIndex=2;
        }else {
            restartAnim();
        }
    }

    elapsed += deltaTime;
    if (elapsed >= frameDuration) {

        if ((newPawnState == PawnState::squat && lastPlayedFrameIndex==3)|| (newPawnState==PawnState::die && lastPlayedFrameIndex==7)){
            elapsed = 0;
            newDirectionAndScale(sprite, direction, scale);
            return getSprite(w, h);;
        }
        lastPlayedFrameIndex++;
        if (lastPlayedFrameIndex >= framesNumber) {
            restartAnim();
        }
        elapsed = 0;
    }

    newDirectionAndScale(sprite, direction, scale);
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