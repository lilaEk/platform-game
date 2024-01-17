#pragma once

#include "stdafx.hpp"

class Stats {

public:
    int level;
    int points;
    long gameTime;
    std::string formattedTime;
    int lives;

    sf::Clock clock;

    sf::Sprite heart;
    sf::Texture heartTexture;

    void initStats();
    void updateStats();
    void render(sf::RenderTarget &target);

private:
    void updateLevel();
    void updatePoints();
    void updateTime();
    void updateLives();

    void getFormattedTime(sf::Time time);

};
