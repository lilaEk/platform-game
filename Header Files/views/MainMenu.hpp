#pragma once

#include <functional>
#include "../stdafx.hpp"
#include "../gameplay/map/MapManager.hpp"
#include "../gameplay/pawns/Player.hpp"
#include "ButtonType.hpp"
#include "Button.hpp"
#include "TextInput.hpp"

class MainMenu {

public:
    using ButtonCallback = std::function<void()>;

    MainMenu(MapManager &mapManager, Player *player, sf::RenderWindow &window);

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
    void renderTextInput();

    void resetNotUsingButtons();

    void setStartButtonCallback(ButtonCallback callback);
    void handleStartButtonPress();
    void handleTextEntered( sf::Event &event);

private:
    MapManager &mapManager;
    Player *player;
    sf::RenderWindow &window;

    ButtonCallback startButtonCallback;

    void initButtons(sf::Font font);

    void setRulesSideBlock(sf::RenderWindow& window, sf::Font font);
    void setRankingSideBlock(sf::RenderWindow& window);
    void setLoadGameSideBlock(sf::RenderWindow& window);


    sf::Color sideBlockColor = sf::Color(115, 165, 126); //green

    sf::Color upButtonsColor = sf::Color(194, 78, 29); //orange
    sf::Color downButtonsColor = sf::Color(221, 180, 34); //yellow


    sf::Color buttonChosenColor = sf::Color(255,102,196); //pink

    ButtonType selectedButton = ButtonType::none;
    ButtonType lastButton = ButtonType::none;

    sf::Font font;
    std::string headlineText = "platform game by rozalia";
    sf::Text headline;
    std::vector<Button> picButtons;
    std::vector<Button> textButtons;

    bool isStartClickable = false;
    TextInput playerNick;

    std::array<PlayerChoice,3> playersTypeArray{PlayerChoice::Dude_Monster, PlayerChoice::Owlet_Monster, PlayerChoice::Pink_Monster};
    int playerIndex=0;
};

