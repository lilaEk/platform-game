#include "../Header Files/Game.hpp"

auto main() -> int {
    //init game engine
    Game game;

    const int FPS_LIMIT = 60;
    float FRAME_TIME = 1.0 / FPS_LIMIT; // ile milisekund powinna trwać 1 klatka gry
    //game loop
    while (game.running()) {

        const float deltaTime = game.clock.getElapsedTime().asMilliseconds()/1000.0f;
        if (deltaTime< FRAME_TIME) {
            continue;
        }

        std::cout << "FPS: " << 1.0f / game.clock.getElapsedTime().asSeconds() << std::endl;

        game.update(deltaTime);
        game.render();
        game.clock.restart();
    }
    //end of app

    return 0;
}