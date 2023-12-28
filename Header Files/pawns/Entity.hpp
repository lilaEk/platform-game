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

    sf::Texture texture{};
    sf::Sprite sprite{};

    float scale{};

    Entity();

    virtual void render(sf::RenderTarget &target) = 0;

};