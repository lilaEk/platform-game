#include "../Header Files/Game.hpp"

auto main() -> int {

    Game app;

    const int FPS_LIMIT = 60;
    float FRAME_TIME = 1.0 / FPS_LIMIT;

    while (app.running()) {

        const float deltaTime = app.clock.getElapsedTime().asMilliseconds()/1000.0f;
        if (deltaTime< FRAME_TIME) {
            continue;
        }
//        std::cout << "FPS: " << 1.0f / game.clock.getElapsedTime().asSeconds() << std::endl;

        app.update_and_render(deltaTime);
        app.clock.restart();
    }

    return 0;
}