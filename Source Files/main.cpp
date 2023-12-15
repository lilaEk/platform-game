#include "../Headers/Game.hpp"

auto main() -> int {

    srand(static_cast<unsigned>(time(0)));
    float lastFunctionCallTime = 0.0f;
    const float functionCallInterval = 0.12f;

    //init game engine
    Game game;

    //game loop
    while (game.running())
    {
        // tutaj obliczamy deltaT
        game.deltaTime = game.clock.restart().asSeconds();
        lastFunctionCallTime += game.deltaTime;

        if (lastFunctionCallTime >= functionCallInterval)
        {

            game.update();
            game.render();
            lastFunctionCallTime = 0.0f;
        }

//        game.update();
//        game.render();
    }
    //end of app

    return 0;
}