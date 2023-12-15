#pragma once

#include "Entity.hpp"
//#include "Animation.hpp"
#include "PawnState.hpp"
#include "SFML/Graphics.hpp"


class Pawn {
protected:
    PawnState currentPawnState;
    sf::Texture textureSheet;
//    sf::Sprite sprite;
    sf::IntRect currentFrame;

public:
    virtual ~Pawn() = default;

    virtual void initSprite() = 0;
//    virtual void initTexture(const std::string& texturePath) = 0;
//    virtual void initAnimations() = 0;

    virtual void render(sf::RenderTarget& target) = 0;
    virtual void update() = 0;
    virtual void updateMovement() = 0;
    virtual void updateAnimations() = 0;
//    virtual void changeAnimation()=0;

//    PawnState pawnState;
};