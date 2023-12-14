#pragma once

#include "../Headers/Game.hpp"
#include "Pawns.hpp"
#include "Entity.hpp"

//class Entity;
//class Pawns;

class Player : Pawns{

private:
    sf::Sprite sprite;
    sf::Texture textureSheet;

    //animation
    sf::IntRect currentFrame;

    //movement
    //core

    void initTexture();
    void initSprite();
    void initAnimations();
public:
    Player();
    virtual ~Player();

    void updateMovement();
    void updateAnimations();
    void update();
    void render(sf::RenderTarget& target);
};