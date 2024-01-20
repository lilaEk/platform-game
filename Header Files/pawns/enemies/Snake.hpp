#pragma once

#include "../Enemy.hpp"

class Snake : public Enemy {

public:
    Snake();

    void init();
    void initAnimations() override;
    void update(float deltaTimem, bool moveable) override;
    void updateAnimations(float deltaTime) override;
    void render(sf::RenderTarget &target) override;
};
