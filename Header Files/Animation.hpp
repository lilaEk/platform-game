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
    float elapsed = 0; //czas jaki upłynął
    const float frameDuration = 120/1000.0f; //ms
    PawnState *lastPawnState;

public:
    int framesNumber; //klatki animacji
    int lastPlayedFrameIndex = 0; //ostatnia klatka
    const std::string assetPath; //scieżka do assetu


    Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *currentPawnState);

    virtual ~Animation();

    sf::Sprite
    getCurrentAnimImg(float deltaTime, int w, int h, Direction direction, float scale, PawnState newPawnState);

    static void newDirectionAndScale(sf::Sprite &sprite, Direction direction, float scale);

    void restartAnim();

    sf::Sprite getSprite(int w, int h);

};