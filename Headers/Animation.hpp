#pragma once

#include "iostream"
#include "SFML/Graphics.hpp"

#include "PawnState.hpp"
#include "Direction.hpp"


class Animation {

protected:
    sf::Texture texture;
    const int frameDuration = 120;
    sf::Sprite sprite; //widoczny obrazek
    long elapsed; //czas jaki upłynął
    PawnState lastState = PawnState::pic;
    Direction lastDirection=Direction::right;

public:
    int framesNumber; //klatki animacji
    int lastPlayedFrameIndex; //ostatnia klatka
    std::string assetPath; //scieżka do assetu

    Animation(std::string assetPath, int framesNumber);
    virtual ~Animation();

    int restartAnim();
    void getCurrentAnimImg(long deltaT, int w, int h, PawnState currentAnim, Direction direction);
//    void rotateLeft(int w);

//    void setTexture(const std::string& newAssetPath, int newFramesNumber);

//    void drawEntities(){
//        for(Enity e : Enity.allEntities()){
//            e.draw()
//        }
//    }

};