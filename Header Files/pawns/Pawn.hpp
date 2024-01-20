#pragma once

#include "Entity.hpp"
#include "enums/PawnState.hpp"
#include "SFML/Graphics.hpp"
#include "enums/Direction.hpp"
#include "enums/PlayerChoice.hpp"


class Pawn : public Entity{

protected:

public:
    virtual ~Pawn() = default;

    float movementSpeed{};

    PawnState lastPawnState{};
    PawnState currentPawnState{};

    Direction direction{};
    bool isJumping{};
    bool isFalling{};

    virtual void initPawn() = 0;
    virtual void initAnimations()=0;
    virtual void update(float d, bool moveable) = 0;
    virtual void updateAnimations(float d) = 0;

};