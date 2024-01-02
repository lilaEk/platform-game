#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "gameplay/map/MapManager.hpp"
#include "gameplay/pawns/Player.hpp"
#include "views/ViewType.hpp"
#include "views/MainMenuView.hpp"
#include "views/NextLevelView.hpp"
#include "views/GameplayView.hpp"
#include "views/GameOverView.hpp"

using namespace sf;

class Game {

public:
    Game();
    virtual ~Game();

    ViewType currentView;
    ViewType lastView;
    RenderWindow window;
    sf::Clock clock;

    bool running() const;    //accessors

    void pollEvents();
    void update_and_render(float d);

    const RenderWindow& getWindow() const;

    static const int height = 3*16*12;
    static const int width = 3*16*20;

private:

    View view;
    Event e;
    Player* player;
    MapManager* mapManager;

    MainMenuView mainMenuView;
    NextLevelView nextLevelView;
    GameplayView gameplayView;
    GameOverView gameOverView;

    static void drawBackgroundImage(sf::RenderWindow &window); //todo - parallex background
};
