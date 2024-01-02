#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"
#include "ViewType.hpp"
#include "MainMenuView.hpp"
#include "NextLevelView.hpp"
#include "GameplayView.hpp"
#include "GameOverView.hpp"

using namespace sf;


class App {
public:
    App();
    virtual ~App();

    ViewType currentView;
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
