#include "../../Header Files/map/MapManager.hpp"

MapManager::MapManager() : currentMap(new Map()) {
}

MapManager::~MapManager() {
    delete currentMap;
}

/*
    // Zwolnij pamięć z map
//    for (auto &pair : maps) {
    // delete pair.second; // Przy założeniu, że Map jest dynamicznie alokowanym obiektem
//    }
//}

//void MapManager::loadMap(const std::string &mapName) {
//    // Sprawdź, czy mapa o danej nazwie już istnieje w Map Managerze
//    auto it = maps.find(mapName);
//    if (it == maps.end()) {
//        // Mapa jeszcze nie wczytana - wczytaj ją
//        Map newMap(mapName);
//        maps.emplace(mapName, std::move(newMap));
//    }
//    // Ustaw nową mapę jako aktywną
//    currentMap = &maps.at(mapName);
//}

//void MapManager::switchMap(const std::string &mapName) {
//    // Przełącz się na inną mapę (działa podobnie do loadMap)
//    auto it = maps.find(mapName);
//    if (it == maps.end()) {
//        Map newMap(mapName);
//        maps.emplace(mapName, std::move(newMap));
//    }
//    currentMap = &maps.at(mapName);
//}
*/

void MapManager::update(float deltaTime) {
    if (currentMap) {
        currentMap->updateMap();
    }
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
