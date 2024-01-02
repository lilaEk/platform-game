#pragma once

#include "../stdafx.hpp"
#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"
#include "ButtonType.hpp"
#include "Button.hpp"

class MainMenuView {

public:
    MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window);

    void handleInput();

    void update(float d);
    void updatePlayer(float d);

    void render();
    void renderPlayer();
    void renderMap();
    void renderButtons();
    void renderHeadline();
    void updateMenuButtons();

    void resetNotUsingButtons();

private:
    MapManager &mapManager;
    Player &player;
    sf::RenderWindow &window;

    void initButtons(sf::Font font);

    sf::Color rulesColor = sf::Color(115, 165, 126); //green
    sf::Color loadGameColor = sf::Color(214,181,167); //red
    sf::Color rankingColor = sf::Color(193,162,255); //violet
    sf::Color buttonChosenColor = sf::Color(255,102,196); //pink

    ButtonType selectedButton = ButtonType::none;
    ButtonType lastButton = ButtonType::none;

    sf::Font font;
    std::string headlineText = "platform game by rozalia";
    sf::Text headline;
    std::vector<Button> buttons;
};

