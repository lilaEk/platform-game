#pragma once

#include "Entity.hpp"
#include "enums/PawnState.hpp"
#include "SFML/Graphics.hpp"
#include "enums/Direction.hpp"
#include "enums/PlayerChoice.hpp"


class Pawn : public Entity{

protected:

public:
    float movementSpeed{};

    PawnState lastPawnState{};

    Direction direction{};

    bool isJumping{};
    bool isFalling{};

    PawnState currentPawnState{};

    virtual ~Pawn() = default;

    virtual void initPlayer() = 0;
    virtual void initAnimations()=0;
//    virtual void render(sf::RenderTarget &target) = 0;
    virtual void update(float d, bool moveable) = 0;
//    virtual void updateMovement(float d) = 0;
    virtual void updateAnimations(float d) = 0;

};