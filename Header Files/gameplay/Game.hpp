#pragma once

#include "Game.hpp"
#include "../stdafx.hpp"
#include "pawns/Player.hpp"
#include "map/MapManager.hpp"

using namespace sf;

class Game { //acts like the game engine

private:
    VideoMode vm;
    Event e;
    Player* player;
    MapManager* mapManager;

    void initWindow();
    static void drawBackgroundImage(RenderWindow &window); //todo - parallex background
    void initMap();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    RenderWindow window;
    sf::Clock clock;
    float currentTime;

    const bool running() const;    //accessors

    void pollEvents();
    void update(float d);
    void updatePlayer(float d);
    void updateMap(float d);
    void render();
    void renderPlayer();
    void renderMap();

    const RenderWindow& getWindow() const;

    static const int height = 3*16*12;
    static const int width = 3*16*20;


};

