#include "../Headers/Game.hpp"

auto main() -> int {

    srand(static_cast<unsigned>(time(0)));
    
    //init game engine
    Game game;

    //game loop
    while (game.running())
    {
        // tutaj obliczamy deltaT

        game.update(); //deltaT w nawiasie
        game.render();
    }
    //end of app

    return 0;
}