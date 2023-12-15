#pragma once

//#include "../Headers/Game.hpp"
#include "iostream"
#include "SFML/Graphics.hpp"

#include "PawnState.hpp"


class Animation {

protected:
    const int frameDuration = 120;
    sf::Sprite sprite; //widoczny obrazek
    long elapsed; //czas jaki upłynął
    PawnState currentAnim = PawnState::pic; //obecna animacja

public:
    int framesNumber; //klatki animacji
    int lastPlayedFrameIndex; //ostatnia klatka
    std::string assetPath; //scieżka do assetu

    Animation(std::string assetPath, int framesNumber);
    virtual ~Animation();

    int restartAnim();
    void getCurrentAnimImg(long deltaT, int w, int h);

//    void drawEntities(){
//        for(Enity e : Enity.allEntities()){
//            e.draw()
//        }
//    }

};