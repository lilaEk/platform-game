#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"


class Entity;

class Entity {

private:
    std::vector<Entity *> allEntities;

public:
    int height{};
    int width{};

    float pos_x{};
    float pos_y{};

    sf::Texture textureSheet{};
    sf::Sprite sprite{};


    Entity();
};