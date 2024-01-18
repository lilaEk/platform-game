#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

#include "pawns/enums/PawnState.hpp"
#include "pawns/enums/Direction.hpp"


class Animation {

private:
    sf::Texture texture;
    sf::Sprite sprite;
    PawnState *lastPawnState;

    float scale;
    float elapsed = 0;
    const float frameDuration = 60/1000.0f; //ms

public:
    int framesNumber;
    int lastPlayedFrameIndex = 0;
    const std::string assetPath;

    Animation() = default;
    Animation(const std::string &assetPath, int framesNumber, float scale, PawnState *currentPawnState);
    virtual ~Animation();

    Animation& operator=(const Animation& other);

    sf::Sprite getCurrentAnimImg(float deltaTime, int w, int h, Direction direction, float scale, PawnState newPawnState);
    static void newDirectionAndScale(sf::Sprite &sprite, Direction direction, float scale);
    void restartAnim();
    sf::Sprite getSprite(int w, int h);
};