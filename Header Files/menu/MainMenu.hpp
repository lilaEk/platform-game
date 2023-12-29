#pragma once
#include "../stdafx.hpp"

class MainMenu {
public:
    MainMenu(float width, float height);

    void draw(sf::RenderWindow & window);

    int MainMenuPressed(){
        return MainMenuSelected;
    }

    ~MainMenu();

private:
    int MainMenuSelected;
    sf::Font font;

};

