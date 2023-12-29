#include "../../Header Files/menu/MainMenu.hpp"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")){
        std::cout << "ERROR: Could not load font from file\n";
    }
}