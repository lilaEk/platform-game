#pragma once

#include "../Header Files/Game.hpp"
#include "../Header Files/stdafx.hpp"
#include "pawns/Player.hpp"


using namespace sf;

class Game { //acts like the game engine - wrapper class

private:
    VideoMode vm;
    Event e;
    Player* player;

    void initWindow();
    static void drawBackgroundImage(RenderWindow &window); //todo - parallex background
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
    void render();
    void renderPlayer();

    const RenderWindow& getWindow() const;

    static const int height = 3*16*12;
    static const int width = 3*16*20;


};

