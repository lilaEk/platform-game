#pragma once

#include <array>
#include "stdafx.hpp"
//#include "Game.hpp"

class Stats {

public:
    int level;
    int points;
    int power;
    std::string formattedTime;
    double lives;

    std::vector<sf::Text> stats;

    void initStats();
    void updateStats(sf::Clock& gameplayClock);
    void render(sf::RenderTarget &target);

    void addLive();
    void removeLive(double value);
    void addPoints(int pointsToAdd);
    void addPower(int powerPointsToAdd);
    sf::Time elapsedTime;

private:
    sf::Sprite heartSprite;
    sf::Texture heartFull;
    sf::Texture heartHalf;
    sf::Texture heartEmpty;
    sf::Font font;

    sf::RectangleShape statsBar;
    std::vector<sf::Text> texts;
    std::string hearts[5];

    void updateLevel();
    void updatePower();
    void updatePoints();
    void updateTime(sf::Clock& gameplayClock);
    void updateLives();

    void renderHearts(sf::RenderTarget &target);

    std::string getFormattedTime(sf::Time time);



};
