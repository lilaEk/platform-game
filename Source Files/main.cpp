#include "../Headers/Game.hpp"
#include "../Headers/stdafx.hpp"


auto main() -> int {

    srand(static_cast<unsigned>(time(0)));
    
    //init game engine
    Game game;

    //game loop
    while (game.running())
    {
        game.update();
        game.render();
    }
    //end of app

    return 0;
}