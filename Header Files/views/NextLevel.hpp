#pragma once

#include "../pawns/Player.hpp"
#include "../map/MapManager.hpp"
#include "../Stats.hpp"
#include <functional>

class NextLevel {
public:
    using KeyCallback = std::function<void(sf::Keyboard::Key)>;

    NextLevel(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats);

    void update(float d);
    void updatePlayer(float d);
    void render();
    void renderPlayer();
    void renderMap();
    void renderHeadline();
    void renderTextProgressSaved();
    void renderTextToContinue();

    void setKeyCallback(KeyCallback callback);

private:
    MapManager& mapManager;
    Player* player;
    sf::RenderWindow& window;
    sf::Font font;
    Stats* stats;

    sf::Text headline;
    sf::Text progressSaved;
    sf::Text textToContinue;

    KeyCallback keyCallback;
};
