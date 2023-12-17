#pragma once

#include "Entity.hpp"
//#include "Animation.hpp"
#include "PawnState.hpp"
#include "SFML/Graphics.hpp"
#include "Direction.hpp"


class Pawn {
protected:
    PawnState currentPawnState;
    PawnState lastPawnState = PawnState::pic;
    sf::Texture textureSheet;
    sf::IntRect currentFrame;
    Direction direction;

public:
    virtual ~Pawn() = default;

    virtual void initSprite() = 0;
//    virtual void initTexture(const std::string& texturePath) = 0;
//    virtual void initAnimations() = 0;

    virtual void render(sf::RenderTarget& target) = 0;
    virtual void update(float d) = 0;
    virtual void updateMovement(float d) = 0;
    virtual void updateAnimations(float d) = 0;

};