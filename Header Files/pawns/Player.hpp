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

    void initPlayer() override;
    void initAnimations() override;

public:
    Player(PlayerChoice playerChoice);
    ~Player() override;

    void render(sf::RenderTarget &target) override;
    void update(float d, bool moveable) override;
    void updateAnimations(float d) override;

    sf::FloatRect getBoundingBox();
};