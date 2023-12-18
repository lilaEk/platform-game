#include "../Headers/Game.hpp"

auto main() -> int {

    float lastFunctionCallTime = 0.0f;
    const float functionCallInterval = 0.12f;

    //init game engine
    Game game;

    game.window.setFramerateLimit(60);

    //game loop
    while (game.running()) {

        game.currentTime = game.clock.restart().asSeconds();
        std::cout<<"current time: "<<game.currentTime<<std::endl;

        float fps = 1.0F / (game.currentTime);
        std::cout<<"fps: "<<fps<<std::endl;

        lastFunctionCallTime += game.currentTime;

        if (lastFunctionCallTime >= functionCallInterval) {
            game.update(game.currentTime);
            game.render();
            lastFunctionCallTime = 0.0f;
        }

    }
    //end of app

    return 0;
}