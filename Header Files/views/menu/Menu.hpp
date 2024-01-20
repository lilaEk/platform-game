#pragma once

#include <functional>
#include "../../stdafx.hpp"
#include "../../map/MapManager.hpp"
#include "../../pawns/Player.hpp"
#include "ButtonType.hpp"
#include "Button.hpp"
#include "TextInput.hpp"
#include "../../pawns/enums/PlayerChoice.hpp"
#include "algorithm"
#include "../../Stats.hpp"

class Menu {

public:
    using ButtonCallback = std::function<void()>;

    Menu(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats);

    TextInput playerNick;
    std::string nick;

    void init();

    void handleButtonClick(int mouseX, int mouseY);

    void update(float d, const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData);
    void updatePlayer(float d);
    void updateMenuButtons(const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData);

    void render();
    void renderPlayer();
    void renderMap();
    void renderButtons();
    void renderHeadline();
    void renderTextInput();

    void resetNotUsingButtons();

    void setStartButtonCallback(ButtonCallback callback);
    void handleStartButtonPress();
    std::string handleTextEntered();

private:
    MapManager &mapManager;
    Player *player;
    sf::RenderWindow &window;
    Stats *stats;

    ButtonCallback startButtonCallback;

    void initButtons();

    void setRulesSideBlock(sf::RenderWindow& window, sf::Font font);
    void setRankingSideBlock(sf::RenderWindow& window, const std::vector<std::tuple<std::string, int, int, int, double, std::string>>& rankingData);
    void setLoadGameSideBlock(sf::RenderWindow& window);
    void drawSideBlockAndHeadline(std::string headline, sf::RenderWindow& window);

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
    bool gameChooseToLoad=false;
    int xChosenGame=0;
    int yChosenGame=0;
    void resetLoadGameValues();

    std::array<PlayerChoice,3> playersTypeArray{PlayerChoice::Dude_Monster, PlayerChoice::Owlet_Monster, PlayerChoice::Pink_Monster};
    int playerIndex=0;

    bool isFileInFolder(const std::string &fileName, const std::string &folderPath);
    bool doesFileNameMatch(const std::string &partialFileName);

    void renderRanking(const std::vector<std::tuple<std::string, int, int, int, double, std::string>> &rankingData);

    std::vector<std::string> getPlayableGames();

    void renderGamesToLoad(const std::vector<std::string> &playableGames,const sf::Vector2i& mousePosition);

    void loadGameDataFromSave(const std::string &gameFileName);
};

