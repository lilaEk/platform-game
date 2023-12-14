#pragma once

#include "Pawn.hpp"

class Player : public Pawn {

private:
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