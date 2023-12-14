#include "../Headers/Game.hpp"
#include "../Headers/Animation.hpp"

Animation::Animation(std::string assetPath, int framesNumber) :
assetPath(assetPath), framesNumber(framesNumber){
    sf::Texture texture;
    if (!texture.loadFromFile(assetPath)) {
        //obsluga bledu
    }

    this->sprite = sf::Sprite(texture);
    this->lastPlayedFrameIndex=0;
}

Animation::~Animation() { }

int Animation::restartAnim() {
    return this->lastPlayedFrameIndex=0;
}

void Animation::getCurrentAnimImg(long deltaT){
    int width=32; //do zmiany przez konstruktor
    int height=32;

//    if(this->currentAnim != this){
//        restartAnim();
//    }
//    this->currentAnim = this;

    this->elapsed += deltaT;
    if (this->elapsed >= this->frameDuration) {
        this->lastPlayedFrameIndex++;
        if (this->lastPlayedFrameIndex >= this->framesNumber) {
            this->lastPlayedFrameIndex = 0;
        }
        this->elapsed = 0;
    }

    if (this->lastPlayedFrameIndex==this->framesNumber-1) {
        restartAnim();
        sf::IntRect currentFrame=sf::IntRect(0, 0, width, height);
        sprite.setTextureRect(currentFrame);
        return;
    }
    this->lastPlayedFrameIndex+=1;
    sf::IntRect currentFrame=sf::IntRect((this->lastPlayedFrameIndex)*width, 0, width, height);
    sprite.setTextureRect(currentFrame);
}