#pragma once

#include "Pawn.hpp"
#include "Animation.hpp"

class Player : public Pawn {

private:
    const float scale = 2.5f;
//    Animation pic = Animation("../assets/player/Pink_Monster/Pic.png", 1);
    Animation idle = Animation("../assets/player/Pink_Monster/Idle.png", 4, scale, &this->lastPawnState);
    Animation run = Animation("../assets/player/Pink_Monster/Run.png", 6, scale, &this->lastPawnState);
    Animation jump = Animation("../assets/player/Pink_Monster/Jump.png", 8, scale, &this->lastPawnState);
      Animation death = Animation("../assets/player/Pink_Monster/Death.png", 8, scale, &this->lastPawnState);
////    Animation roll = Animation("../assets/player/Pink_Monster/Roll.png");
////    Animation squat = Animation("../assets/player/player/Pink_Monster/Squat.png");
////    Animation happy = Animation("../assets/player/Pink_Monster/Happy.png");
    Animation push = Animation("../assets/player/Pink_Monster/Push.png", 6, scale, &this->lastPawnState);
////    Animation lift = Animation("../assets/player/Pink_Monster/Lift.png");
    Animation hurt = Animation("../assets/player/Pink_Monster/Hurt.png", 4, scale, &this->lastPawnState);
//    Animation directAttack = Animation("../assets/player/Pink_Monster/Attack.png", 4);
    Animation directDoubleAttack = Animation("../assets/player/Pink_Monster/Attack_Double.png", 6, scale, &this->lastPawnState);
    Animation throwAttack = Animation("../assets/player/Pink_Monster/Throw.png", 4, scale, &this->lastPawnState);

    int width = 32;
    int height = 32;

    void initPlayer() override;

public:
    Player();
    ~Player() override;

    void render(sf::RenderTarget &target) override;

    void update(float d) override;
    void updateMovement(float d) override;
    void updateAnimations(float d) override;

    sf::Sprite sprite;

    float position_x = 0.0f + width;
    float position_y = 450.f;
    float movement_speed = 350.f;
};