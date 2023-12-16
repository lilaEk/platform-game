#include "../Headers/Animation.hpp"

Animation::Animation(std::string assetPath, int framesNumber) :
        assetPath(assetPath), framesNumber(framesNumber) {
    sf::Texture texture;
    if (!texture.loadFromFile(assetPath)) {
        //obsluga bledu
    }

    this->sprite = sf::Sprite(texture);
    this->lastPlayedFrameIndex = 0;
}

Animation::~Animation() {}

int Animation::restartAnim() {
    return this->lastPlayedFrameIndex = 0;
}

void Animation::getCurrentAnimImg(long deltaT, int w, int h, PawnState currentAnim, Direction direction) {

    checkDirection(direction);
    checkAnimation(currentAnim);

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
        sf::IntRect currentFrame = sf::IntRect(0, 0, w, h);
        sprite.setTextureRect(currentFrame);
        return;
    }
    this->lastPlayedFrameIndex += 1;
    sf::IntRect currentFrame = sf::IntRect(
            (this->lastPlayedFrameIndex) * w, 0, w, h);
    sprite.setTextureRect(currentFrame);
}

void Animation::checkDirection(Direction direction) {
    if (direction != this->lastDirection) {
        if (direction == Direction::left) {
            sprite.setScale(-2.5f, 2.5f);
        } else if (direction == Direction::right) {
            sprite.setScale(2.5f, 2.5f);
        }

        sf::FloatRect bounds = sprite.getLocalBounds();
        sf::Vector2f oldPosition = sprite.getPosition();

        if (direction == Direction::left) {
            sprite.setPosition(oldPosition.x + bounds.width * 2.5f, oldPosition.y);
        } else if (direction == Direction::right) {
            sprite.setPosition(oldPosition.x - bounds.width * 2.5f, oldPosition.y);
        }

        this->lastDirection = direction;
    }
}

void Animation::checkAnimation(PawnState currentAnim) {
    switch (currentAnim) {
        case PawnState::run:
            if (this->lastState != PawnState::run) {
                this->lastPlayedFrameIndex = 0;
                this->lastState = PawnState::run;
                this->framesNumber = 6;
                if (!texture.loadFromFile("../assets/Pink_Monster/Run.png")) {
                    std::cout << "ERROR: Could not load texture from file\n";
                }
                this->sprite.setTexture(texture);
                break;
            }

            break;
            // Dodac inne przypadki dla różnych stanów postaci
        default:
            if (this->lastState != PawnState::idle) {
                this->lastPlayedFrameIndex = 0;
                this->lastState = PawnState::idle;
                this->framesNumber = 4;
                if (!texture.loadFromFile("../assets/Pink_Monster/Idle.png")) {
                    // Obsłuż błąd ładowania tekstury
                    std::cout << "ERROR: Could not load texture from file\n";
                }
                this->sprite.setTexture(texture);
            }
            break;
    }
}
