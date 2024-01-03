#pragma once

#include <functional>
#include "../stdafx.hpp"
#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"
#include "ButtonType.hpp"
#include "Button.hpp"

class MainMenuView {

public:
    using ButtonCallback = std::function<void()>;

    sf::String playerNick;
    sf::Text playerText;

    MainMenuView(MapManager &mapManager, Player &player, sf::RenderWindow &window);

    void handleInput();
    void handleButtonClick(int mouseX, int mouseY);

    void update(float d);
    void updatePlayer(float d);
    void updateMenuButtons();

    void render();
    void renderPlayer();
    void renderMap();
    void renderButtons();
    void renderHeadline();

    void resetNotUsingButtons();

    void setStartButtonCallback(ButtonCallback callback);
    void handleStartButtonPress();

private:
    MapManager &mapManager;
    Player &player;
    sf::RenderWindow &window;

    ButtonCallback startButtonCallback;

    void initButtons(sf::Font font);

    void setRulesSideBlock(sf::Color rulesColor, sf::RenderWindow& window, sf::Font font);

    sf::Color rulesColor = sf::Color(115, 165, 126); //green
    sf::Color loadGameColor = sf::Color(214,181,167); //red
    sf::Color rankingColor = sf::Color(193,162,255); //violet
    sf::Color buttonChosenColor = sf::Color(255,102,196); //pink

    ButtonType selectedButton = ButtonType::none;
    ButtonType lastButton = ButtonType::none;

    sf::Font font;
    std::string headlineText = "platform game by rozalia";
    sf::Text headline;
    std::vector<Button> picButtons;
    std::vector<Button> textButtons;

    bool isStartClickable = false;

};

