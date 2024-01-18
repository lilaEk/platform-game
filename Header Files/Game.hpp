#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "map/MapManager.hpp"
#include "pawns/Player.hpp"
#include "views/ViewType.hpp"
#include "views/menu/Menu.hpp"
#include "views/NextLevel.hpp"
#include "views/Gameplay.hpp"
#include "views/GameOver.hpp"

using namespace sf;

class Game {

public:
    Game();
    virtual ~Game();

    ViewType currentView;
    ViewType lastView;
    RenderWindow window;
    sf::Clock clock;

    int powerLevelGoal=16;

    bool running() const;
    void pollEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void update_and_render(float d);

    const RenderWindow& getWindow() const;

    static const int height = 624; //48*13
    static const int width = 960; //48*20

private:

    View view;
    Event e;
    Player* player;
    MapManager* mapManager;
    Stats stats;

    sf::Clock gameplayClock;

    Menu mainMenuView;
    NextLevel nextLevelView;
    Gameplay gameplayView;
    GameOver gameOverView;

    static void drawBackgroundImage(sf::RenderWindow &window); //todo - parallex background
    void resetGameplayClock();

    void resetGameplay();
};
