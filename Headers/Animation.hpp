#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

#include "PawnState.hpp"
#include "Direction.hpp"


class Animation {

private:
    float scale;
    sf::Texture texture;
    const int frameDuration = 120;
    sf::Sprite sprite; //widoczny obrazek
    long elapsed=0; //czas jaki upłynął

public:
    const int framesNumber; //klatki animacji
    int lastPlayedFrameIndex = 0; //ostatnia klatka
    const std::string assetPath; //scieżka do assetu

    Animation(const std::string &assetPath, int framesNumber);
    Animation(const std::string &assetPath, int framesNumber, float scale);
    virtual ~Animation();

    sf::Sprite getCurrentAnimImg(long deltaT, int w, int h);

    static void checkDirection(sf::Sprite &sprite, Direction direction,float scale);

    int restartAnim();

};