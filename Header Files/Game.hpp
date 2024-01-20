#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "map/MapManager.hpp"
#include "pawns/Player.hpp"
#include "views/ViewType.hpp"
#include "views/menu/Menu.hpp"
#include "views/NextLevel.hpp"
#include "views/Gameplay.hpp"
#include "views/GameOver.hpp"
#include "pawns/Enemy.hpp"
#include <fstream>
#include <filesystem>

using namespace sf;

class Game {

public:
    Game();
    virtual ~Game();

    std::string nick;

    ViewType currentView;
    ViewType lastView;
    RenderWindow window;
    sf::Clock clock;

    int powerLevelGoal=20;

    bool running() const;
    void pollEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void update_and_render(float d);

    const RenderWindow& getWindow() const;

    static const int height = 624; //48*13
    static const int width = 960; //48*20

private:
    std::string rankingFilePath = "ranking.csv";

    View view;
    Event e;
    Player* player;
    MapManager* mapManager;
    Stats stats;

    Menu mainMenuView;
    NextLevel nextLevelView;
    Gameplay gameplayView;
    GameOver gameOverView;

    static void drawBackgroundImage(sf::RenderWindow &window); //todo - parallex background

    void resetGameplay();

    void saveStatsToCSV(const std::string &filename);

    void generateRanking();

    std::vector<std::tuple<std::string, int, int, int, double, std::string>> playerData;

    void processFile(const std::filesystem::directory_entry &entry);
};
