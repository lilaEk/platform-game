#pragma once

#include <array>
#include "stdafx.hpp"
#include "views/ViewType.hpp"

class Stats {

public:
    int level;
    int points;
    int power;
    std::string formattedTime;
    double lives;

    std::vector<sf::Text> stats;

    sf::Clock gameClock;
    sf::Clock breakClock;
    sf::Time totalElapsedTime;
    sf::Time breakElapsedTime;

    sf::Time allBreaksElapsedTime;

    sf::Time breakStartTime;

    bool inBreak=true;

    void initStats();
    void initBasicValues();

    void updateStats(ViewType currentView);
    void render(sf::RenderTarget &target);

    void addLive();
    void removeLive(double value);
    void addPoints(int pointsToAdd);
    void addPower(int powerPointsToAdd);

//    sf::Time elapsedTime;
//    sf::Time totalElapsedTime;

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
    void updateTime(ViewType currentView);
    void updateLives();

    void renderHearts(sf::RenderTarget &target);

    std::string getFormattedTime(sf::Time time);


};
