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

void Animation::getCurrentAnimImg(long deltaT, int w, int h, PawnState currentAnim){
/*
        if(this->currentAnim != this){
        restartAnim();
    }
    this->currentAnim = this;
*/

    switch (currentAnim) {
        case PawnState::run:
            if (this->lastState!=PawnState::run) this->lastPlayedFrameIndex=0;
            this->lastState=PawnState::run;
            this->framesNumber=6;
            if (!texture.loadFromFile("../assets/Pink_Monster/Pink_Monster_Run.png")) {
                // Obsłużyc błąd ładowania tekstury
                std::cout << "ERROR: Could not load texture from file\n";
            }
            this->sprite.setTexture(texture);
            break;
            // Dodac inne przypadki dla różnych stanów postaci
        default:
            if (this->lastState!=PawnState::idle) this->lastPlayedFrameIndex=0;
            this->lastState=PawnState::idle;
            this->framesNumber=4;
            if (!texture.loadFromFile("../assets/Pink_Monster/Pink_Monster_Idle.png")) {
                // Obsłuż błąd ładowania tekstury
                std::cout << "ERROR: Could not load texture from file\n";
            }
            this->sprite.setTexture(texture);
            break;
    }

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
        sf::IntRect currentFrame=sf::IntRect(0, 0, w, h);
        sprite.setTextureRect(currentFrame);
        return;
    }
    this->lastPlayedFrameIndex+=1;
    sf::IntRect currentFrame=sf::IntRect((this->lastPlayedFrameIndex)*w, 0, w, h);
    sprite.setTextureRect(currentFrame);
}

//void Animation::setTexture(const std::string& newAssetPath, int newFramesNumber) {
//    assetPath = newAssetPath;
//    framesNumber = newFramesNumber;
//
//    sf::Texture texture;
//    if (!texture.loadFromFile(assetPath)) {
//        // Obsługa błędu ładowania tekstury
//    }
//
//    sprite.setTexture(texture);
//    lastPlayedFrameIndex = 0;
//}