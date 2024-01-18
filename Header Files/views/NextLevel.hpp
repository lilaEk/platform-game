#pragma once

#include "../pawns/Player.hpp"
#include "../map/MapManager.hpp"

class NextLevel {
public:
    NextLevel(MapManager &mapManager, Player *player, sf::RenderWindow &window, int *level);

    void handleInput();

    void update(float d);
    void updatePlayer(float d);
    void render();
    void renderPlayer();
    void renderMap();
    void renderHeadline();
    void renderTextProgressSaved();
    void renderTextToContinue();

private:
    MapManager& mapManager;
    Player* player;
    sf::RenderWindow& window;
    sf::Font font;

    sf::Text headline;
    sf::Text progressSaved;
    sf::Text textToContinue;

    int *level;
};
