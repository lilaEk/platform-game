#pragma once

#include <functional>
#include "../map/MapManager.hpp"
#include "../pawns/Player.hpp"
#include "../Stats.hpp"

class GameOver {
public:
    using KeyCallback = std::function<void(sf::Keyboard::Key)>;

    GameOver(MapManager &mapManager, Player *player, sf::RenderWindow &window, Stats *stats);

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

