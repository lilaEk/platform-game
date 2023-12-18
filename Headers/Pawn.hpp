#pragma once

#include "Entity.hpp"
//#include "Animation.hpp"
#include "PawnState.hpp"
#include "SFML/Graphics.hpp"
#include "Direction.hpp"


class Pawn {

protected:
    PawnState currentPawnState = PawnState::idle;
    sf::Texture textureSheet;
    Direction direction;

    bool isJumping = false;


public:
    virtual ~Pawn() = default;

    virtual void initPlayer() = 0;

    virtual void render(sf::RenderTarget& target) = 0;
    virtual void update(float d) = 0;
    virtual void updateMovement(float d) = 0;
    virtual void updateAnimations(float d) = 0;

};