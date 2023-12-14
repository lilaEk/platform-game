#pragma once

#include "../Headers/Game.hpp"


class Entity {

private :
    std::vector<Entity *> allEntities;

public:
    float pos_x = 0; //todo
    float pos_y = 0;

    // w pixelach
    int height;
    int width;

    Entity();

//    void addEntityToVec(std::vector<Entity*> &allEntities, Entity& entity);
};