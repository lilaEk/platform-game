#include "../../Header Files/views/App.hpp"

App::App() : player(new Player),
            mapManager(new MapManager),
            window(sf::VideoMode(App::width, App::height), "platform game by rozalia",
                   sf::Style::Titlebar | sf::Style::Close),
            mainMenuView(*this->mapManager, *this->player, this->window),
            gameplayView(*this->mapManager, *this->player, this->window),
            nextLevelView(*this->mapManager, *this->player, this->window),
            gameOverView(*this->mapManager, *this->player, this->window) {

    this->view.setSize(static_cast<float>(App::width), static_cast<float>(App::height));
    this->view.setCenter(static_cast<float>(App::width) / 2.f, static_cast<float>(App::height) / 2.f);
    this->window.setView(this->view);

    this->currentView = ViewType::main_menu;
}

App::~App() {
    delete this->player;
    delete this->mapManager;
}

bool App::running() const {
    return this->window.isOpen();
}

void App::pollEvents() {

    while (this->window.pollEvent(this->e)) {
        switch (this->e.type) {
            case Event::Closed:
                this->window.close();
                break;
            case Event::KeyPressed:
                if (e.key.code == Keyboard::Escape)
                    this->window.close();
                break;
        }
    }
}

//void App::updateMap(float deltaTime){
//    this->mapManager->update(deltaTime);
//}

//void App::updatePlayer(float deltaTime) {
//    this->player->update(deltaTime);
//}

void App::update_and_render(float deltaTime) {
    this->pollEvents();

    this->window.clear();
    this->window.setView(this->view);

    this->drawBackgroundImage(this->window);

    switch (this->currentView) {
        case ViewType::main_menu:
            mainMenuView.handleInput();
            mainMenuView.update(deltaTime);
            mainMenuView.render();

            if (1 == 0) {
                this->currentView = ViewType::next_level;
                nextLevelView.init();
            }
            break;

        case ViewType::next_level:
            nextLevelView.handleInput();
            nextLevelView.update(deltaTime);
            nextLevelView.render();

            if (1 == 0) {
                this->currentView = ViewType::gameplay;
                gameplayView.init();
            }
            break;

        case ViewType::gameplay:
            gameplayView.handleInput();
            gameplayView.update(deltaTime);
            gameplayView.render();

            if (1 == 0) {
                this->currentView = ViewType::game_over;
                gameOverView.init();
            }
            break;

        case ViewType::game_over:
            gameOverView.handleInput();
            gameOverView.update(deltaTime);
            gameOverView.render();

            if (1 == 0) {
                this->currentView = ViewType::main_menu;
                mainMenuView.init();
            }
            break;
    }

    this->window.display();
}


const RenderWindow &App::getWindow() const {
    return this->window;
}

void App::drawBackgroundImage(RenderWindow &window) {

    sf::Texture bg1, bg2, bg3, bg5, bg8, bg10;

    if (!bg1.loadFromFile("../assets/background/1.png") ||
        !bg2.loadFromFile("../assets/background/2.png") ||
        !bg3.loadFromFile("../assets/background/3.png") ||
        !bg5.loadFromFile("../assets/background/5.png") ||
        !bg8.loadFromFile("../assets/background/8.png")
            ) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    sf::Sprite background1(bg1);
    sf::Sprite background2(bg2);
    sf::Sprite background3(bg3);
    sf::Sprite background5(bg5);
    sf::Sprite background8(bg8);

    float ratio1 = static_cast<float>(bg1.getSize().x) / bg1.getSize().y;
    float ratio2 = static_cast<float>(bg2.getSize().x) / bg2.getSize().y;
    float ratio3 = static_cast<float>(bg3.getSize().x) / bg3.getSize().y;
    float ratio5 = static_cast<float>(bg5.getSize().x) / bg5.getSize().y;
    float ratio8 = static_cast<float>(bg8.getSize().x) / bg8.getSize().y;

    float minRatio = std::min({ratio1, ratio2, ratio3, ratio5, ratio8});

    background1.setScale(minRatio, minRatio);
    background2.setScale(minRatio, minRatio);
    background3.setScale(minRatio, minRatio);
    background5.setScale(minRatio, minRatio);
    background8.setScale(minRatio, minRatio);

    window.draw(background1);
    window.draw(background2);
    window.draw(background3);
    window.draw(background5);
    window.draw(background8);
}