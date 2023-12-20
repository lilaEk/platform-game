#pragma once

#include <iostream>
#include <vector>

class Entity;

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
};