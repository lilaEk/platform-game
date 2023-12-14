#pragma once

#include "../Headers/Game.hpp"
#include "Pawns.hpp"
#include "PawnState.hpp"


class Animation {

private:
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
    void createAnimation(long deltaT);

//    void drawEntities(){
//        for(Enity e : Enity.allEntities()){
//            e.draw()
//        }
//    }

};