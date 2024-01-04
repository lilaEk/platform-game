#include "../Header Files/Game.hpp"

Game::Game() : player(new Player(PlayerChoice::Dude_Monster)),
               mapManager(new MapManager),
               window(sf::VideoMode(Game::width, Game::height), "platform game by rozalia",
                      sf::Style::Titlebar | sf::Style::Close),
               mainMenuView(*this->mapManager, this->player, this->window),
               gameplayView(this->mapManager, this->player, this->window),
               nextLevelView(*this->mapManager, *this->player, this->window),
               gameOverView(*this->mapManager, *this->player, this->window) {

    this->view.setSize(static_cast<float>(Game::width), static_cast<float>(Game::height));
    this->view.setCenter(static_cast<float>(Game::width) / 2.f, static_cast<float>(Game::height) / 2.f);
    this->window.setView(this->view);

    this->currentView = ViewType::main_menu;
    this->lastView = ViewType::main_menu;

    mainMenuView.setStartButtonCallback([this] { handleStartButtonPress(); });
}

Game::~Game() {
    delete this->player;
    delete this->mapManager;
}

bool Game::running() const {
    return this->window.isOpen();
}

void Game::pollEvents() {

    while (this->window.pollEvent(this->e)) {
        switch (this->e.type) {
            case Event::Closed:
                this->window.close();
                break;
            case Event::KeyPressed:
                if (e.key.code == Keyboard::Escape)
                    this->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (currentView == ViewType::main_menu) {
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        handleMouseClick(e.mouseButton.x, e.mouseButton.y);
                    }
                }
            case sf::Event::TextEntered:
                if (currentView == ViewType::main_menu) {
                    mainMenuView.handleTextEntered(e);
                }
                break;
        }
    }
}

void Game::update_and_render(float deltaTime) {
    this->pollEvents();

    this->window.clear();
    this->window.setView(this->view);

    this->drawBackgroundImage(this->window);

    switch (this->currentView) {
        case ViewType::main_menu:

            if (lastView != currentView) {
                this->mapManager->currentMap->initMap();
                this->player->currentPawnState = PawnState::idle;
                lastView=ViewType::main_menu;
            }

            mainMenuView.handleInput();
            mainMenuView.update(deltaTime);
            mainMenuView.render();

            if (1 == 0) {
                this->currentView = ViewType::next_level;
            }
            break;

        case ViewType::next_level:

            if (lastView != currentView) {
                this->player->currentPawnState = PawnState::happy;
                lastView=ViewType::next_level;
            }

            nextLevelView.handleInput();
            nextLevelView.update(deltaTime);
            nextLevelView.render();

            if (1 == 0) {
                this->currentView = ViewType::gameplay;
            }
            break;

        case ViewType::gameplay:

            if (lastView != currentView) {
                lastView=ViewType::gameplay;
            }

            gameplayView.handleInput();
            gameplayView.update(deltaTime);
            gameplayView.render();

            if (1 == 0) {
                this->currentView = ViewType::game_over;
            }
            break;

        case ViewType::game_over:

            if (lastView != currentView) {
                this->player->currentPawnState = PawnState::die; //ale tylko raz!
            }

            gameOverView.handleInput();
            gameOverView.update(deltaTime);
            gameOverView.render();

            if (1 == 0) {
                this->currentView = ViewType::main_menu;
            }
            break;
    }

    this->window.display();
}


const RenderWindow &Game::getWindow() const {
    return this->window;
}

void Game::drawBackgroundImage(RenderWindow &window) {

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

    float scaleX = static_cast<float>(window.getSize().x) / bg1.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / bg1.getSize().y;

    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    background3.setScale(scaleX, scaleY);
    background5.setScale(scaleX, scaleY);
    background8.setScale(scaleX, scaleY);

    window.draw(background1);
    window.draw(background2);
    window.draw(background3);
    window.draw(background5);
    window.draw(background8);
}

void Game::handleMouseClick(int mouseX, int mouseY) {
    switch (currentView) { //todo do uzupełnienia
        case ViewType::main_menu:
            mainMenuView.handleButtonClick(mouseX, mouseY);
            break;
        default:
            break;
    }
}

void Game::handleStartButtonPress() {
    this->currentView = ViewType::gameplay;
}
