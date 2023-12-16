#pragma once

#include "Pawn.hpp"
#include "Animation.hpp"

class Player : public Pawn, public Animation {

private:
    Animation idle = Animation("../assets/Pink_Monster/Run.png", 4);
    Animation run = Animation("../assets/Pink_Monster/Run.png", 6);
    Animation jump = Animation("../assets/Pink_Monster/Jump.png", 8);
//    Animation jumpAttack = Animation();
    Animation die = Animation("../assets/Pink_Monster/Death.png", 8);
//    Animation roll = Animation("../assets/Pink_Monster/Roll.png");
//    Animation squat = Animation("../assets/Pink_Monster/Squat.png");
//    Animation happy = Animation("../assets/Pink_Monster/Happy.png");
    Animation push = Animation("../assets/Pink_Monster/Push.png", 6);
//    Animation lift = Animation("../assets/Pink_Monster/Lift.png");
    Animation hurt = Animation("../assets/Pink_Monster/Hurt.png", 4);
    Animation directAttack = Animation("../assets/Pink_Monster/Attack.png", 4);
    Animation directDoubleAttack = Animation("../assets/Pink_Monster/Attack_Double.png", 6);
    Animation throwAttack = Animation("../assets/Pink_Monster/Throw.png", 4);


    int width = 32;
    int height= 32;

    sf::Clock clock;
    float deltaTime;

    void initSprite() override;
//    void initTexture(const std::string& texturePath) override;
//    void initAnimations() override;

public:
    Player();
    ~Player() override;

    void render(sf::RenderTarget& target) override;
    void update(float d) override;
    void updateMovement() override;
    void updateAnimations(float d) override;
};