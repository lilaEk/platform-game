#pragma once

#include "../Headers/Game.hpp"
#include "../Headers/stdafx.hpp"
#include "Player.hpp"


using namespace sf;

class Game { //acts like the game engine - wrapper class

private:
    RenderWindow window;
    VideoMode vm;
    Event e;

    Player* player;

    void initWindow();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    const bool running() const;    //accessors

    void pollEvents();
    void update();
    void updatePlayer();
    void render();
    void renderPlayer();
    const RenderWindow& getWindow() const;
};

