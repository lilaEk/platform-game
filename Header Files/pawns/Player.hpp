#pragma once

#include "Pawn.hpp"
#include "../Animation.hpp"
#include "enums/PlayerChoice.hpp"

class Player : public Pawn {

private:
    PlayerChoice chosenPlayer{};

    Animation idle;
    Animation run;
    Animation jump;
    Animation death;
    Animation roll;
    Animation squat;
    Animation happy;
    Animation push;
    Animation climb;
    Animation lift;
    Animation hurt;
    Animation directAttack ;
    Animation directDoubleAttack;
    Animation throwAttack;

    //physics (w pawn) - todo
//    sf::Vector2f vector2F;
//    float acceleration;
//    float deceleration;

    void initPlayer() override;
    void initAnimations(PlayerChoice playerChoice) override;

public:
    Player();
    ~Player() override;

    void render(sf::RenderTarget &target) override;
    void update(float d) override;
    void updateMovement(float d) override;
    void updateAnimations(float d) override;
};