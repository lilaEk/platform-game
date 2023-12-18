#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

#include "PawnState.hpp"
#include "Direction.hpp"


class Animation {

private:
    float scale;
    sf::Texture texture;
    sf::Sprite sprite; //widoczny obrazek
    long elapsed=0; //czas jaki upłynął
    Direction lastDirectionToCompare=Direction::right;

public:
    int framesNumber; //klatki animacji
    int lastPlayedFrameIndex = 0; //ostatnia klatka
    const std::string assetPath; //scieżka do assetu

    Animation(const std::string &assetPath, int framesNumber);
    Animation(const std::string &assetPath, int framesNumber, float scale);
    virtual ~Animation();

    sf::Sprite getCurrentAnimImg(int w, int h,Direction direction, float scale);

    static void newDirection(sf::Sprite &sprite, Direction direction, float scale);

    int restartAnim();

    sf::Sprite getSprite(int w, int h);

};