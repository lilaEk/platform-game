#pragma once

#include "Pawn.hpp"
#include "../Animation.hpp"
#include "PlayerChoice.hpp"

class Player : public Pawn {

private:
    int width = 32;
    int height = 32;

    PlayerChoice chosenPlayer;
    const float scale = 2.5f;

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

    //physics - todo
//    sf::Vector2f vector2F;
//    float acceleration;
//    float deceleration;

    void initPlayer() override;
    void initAnimations(PlayerChoice playerChoice) override;

public:
    sf::Sprite sprite;

    float position_x = 0.0f + width;
    float position_y = 450.f;
    float movement_speed = 350.f;

    Player();
    ~Player() override;

    void render(sf::RenderTarget &target) override;
    void update(float d) override;
    void updateMovement(float d) override;
    void updateAnimations(float d) override;
};