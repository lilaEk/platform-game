#pragma once

#include "../Enemy.hpp"

class ForestBoss : public Enemy {

public:
    ForestBoss();

    void init();
    void initAnimations() override;
    void update(float deltaTimem, bool moveable) override;
    void updateAnimations(float deltaTime) override;
    void render(sf::RenderTarget &target) override;
};
