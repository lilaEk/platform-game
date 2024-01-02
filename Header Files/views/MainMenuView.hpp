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

    ButtonType MenuPressed(){
        return MenuSelected;
    }

private:
    MapManager& mapManager;
    Player& player;
    sf::RenderWindow& window;

    void initButtons(sf::Font font);

    ButtonType MenuSelected;
    sf::Font font;
    std::vector<Button> buttons;
};

