#pragma once

#include <memory>
#include "Pawn.hpp"
#include "../Animation.hpp"
#include "enemies/EnemyType.hpp"

class Snake;
class Enemy : public Pawn {

public:
    Enemy();

    virtual ~Enemy() = default;

    bool moveable;
    EnemyType type;

    std::vector<Enemy*> allEnemies;
    std::string characterFolder;

    Animation run;
    Animation jump;
    Animation death;
    Animation hurt;
    Animation attack ;

//    void initForestBoss();

    void update(float deltaTime, bool moveable) override; //all enemies
    void render(sf::RenderTarget &target) override; //all enemies

    void initPawn() override; //random enemy
    void initAnimations() override;
    void updateAnimations(float d) override;

};