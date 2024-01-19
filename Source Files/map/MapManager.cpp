#include "../../Header Files/map/MapManager.hpp"

MapManager::MapManager() : currentMap(new Map()) {
}

MapManager::~MapManager() {
    delete currentMap;
}

void MapManager::update() {
    currentMap->updateMap();
}

void MapManager::render(sf::RenderWindow &target) {
    if (currentMap) {
        currentMap->renderMap(target);
    }
}

void MapManager::scrollMap(float currentTime) {
    if (currentMap) {
        currentMap->scrollMap(currentTime);
    }
}
