#include "../../Header Files/map/MapManager.hpp"

MapManager::MapManager() : currentMap(new Map()) {
}

MapManager::~MapManager() {
    delete currentMap;
}

void MapManager::update(Enemy& enemy) {
    currentMap->updateMap(enemy);
}

void MapManager::render(sf::RenderWindow &target) {
    if (currentMap) {
        currentMap->renderMap(target);
    }
}

void MapManager::scrollMap(float currentTime,Enemy &enemy) {
    if (currentMap) {
        currentMap->scrollMap(currentTime, enemy);
    }
}
