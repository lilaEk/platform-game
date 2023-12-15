#pragma once

#include "Pawn.hpp"
#include "Animation.hpp"

class Player : public Pawn {

private:
    int width = 32;
    int height= 32;


    void initSprite() override;
    void initTexture(const std::string& texturePath) override;
    void initAnimations() override;

public:
    Player();
    ~Player() override;

    void render(sf::RenderTarget& target) override;
    void update() override;
    void updateMovement() override;
    void updateAnimations() override;
};