#pragma once

#include <array>
#include "stdafx.hpp"

class Stats {

public:
    int level;
    int points;
    int power;
    std::string formattedTime;
    double lives;

    void initStats();
    void updateStats();
    void render(sf::RenderTarget &target);

private:
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Sprite heartSprite;
    sf::Texture heartFull;
    sf::Texture heartHalf;
    sf::Texture heartEmpty;
    sf::Font font;

    sf::RectangleShape statsBar;

    std::vector<sf::Text> texts;
    std::vector<sf::Text> stats;

    std::string hearts[5];

    void updateLevel();
    void updatePoints();
    void updateTime();
    void updateLives();

    void renderHearts(sf::RenderTarget &target);

    std::string getFormattedTime(sf::Time time);



};
