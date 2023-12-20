#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

#include "entities/PawnState.hpp"
#include "Direction.hpp"


class Animation {

private:
    sf::Texture texture;
    sf::Sprite sprite; //widoczny obrazek
    PawnState *lastPawnState;

    float scale;
    float elapsed = 0; //czas jaki upłynął
    const float frameDuration = 120/1000.0f; //ms

public:
    int framesNumber; //klatki animacji
    int lastPlayedFrameIndex = 0; //ostatnia klatka
    const std::string assetPath; //scieżka do assetu

    Animation() = default;
    Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *currentPawnState);
    virtual ~Animation();

    Animation& operator=(const Animation& other);

    sf::Sprite getCurrentAnimImg(float deltaTime, int w, int h, Direction direction, float scale, PawnState newPawnState);
    static void newDirectionAndScale(sf::Sprite &sprite, Direction direction, float scale);
    void restartAnim();
    sf::Sprite getSprite(int w, int h);
};