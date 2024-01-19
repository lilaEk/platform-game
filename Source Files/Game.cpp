#include "../Header Files/Game.hpp"

Game::Game() : player(new Player(PlayerChoice::Dude_Monster)),
               mapManager(new MapManager),
               window(sf::VideoMode(Game::width, Game::height), "platform game by rozalia",
                      sf::Style::Titlebar | sf::Style::Close),
               mainMenuView(*mapManager, player, window),
               gameplayView(*mapManager, player, window, &stats),
               nextLevelView(*mapManager, player, window, &stats),
               gameOverView(*mapManager, player, window, &stats) {

    view.setSize(static_cast<float>(Game::width), static_cast<float>(Game::height));
    view.setCenter(static_cast<float>(Game::width) / 2.f, static_cast<float>(Game::height) / 2.f);
    window.setView(view);

    currentView = ViewType::main_menu;
    lastView = ViewType::main_menu;

    mainMenuView.setStartButtonCallback([this] {
        currentView = ViewType::next_level;
    });
}

Game::~Game() {
    delete player;
    delete mapManager;
}

bool Game::running() const {
    return window.isOpen();
}

void Game::pollEvents() {

    while (this->window.pollEvent(this->e)) {
        switch (e.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (e.key.code == Keyboard::Escape &&
                    (currentView == ViewType::next_level || currentView == ViewType::game_over)) {
                    currentView = ViewType::main_menu;
                } else if (e.key.code == sf::Keyboard::Enter && currentView == ViewType::next_level) {
                    currentView = ViewType::gameplay;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (currentView == ViewType::main_menu) {
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        handleMouseClick(e.mouseButton.x, e.mouseButton.y);
                        stats.gameClock.restart();
                        stats.totalElapsedTime = sf::Time::Zero;
                        stats.allBreaksElapsedTime=sf::Time::Zero;
                        stats.inBreak=false;
                    }
                }
                break;
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

    window.clear();
    window.setView(view);

    drawBackgroundImage(window);

    if (stats.lives < 0.5 && currentView == ViewType::gameplay) {
        currentView = ViewType::game_over;
    }

    stats.updateStats(currentView);

    switch (currentView) {
        case ViewType::main_menu:

            if (lastView != currentView) {
                if (lastView != ViewType::next_level) { mapManager->currentMap->initMap(); }
                player->currentPawnState = PawnState::idle;
                resetGameplay();
                lastView = ViewType::main_menu;
            }
            mainMenuView.update(deltaTime);
            mainMenuView.render();
            break;

        case ViewType::next_level:

            if (lastView != currentView) {
                player->currentPawnState = PawnState::happy;
                lastView = ViewType::next_level;

                player->pos_x = 480;
                player->pos_y = Game::height - 48 * 2.5 + 24;

                if (stats.level != 1) {
                    mapManager->currentMap->initMap();
                }
                stats.breakClock.restart();
            }
            nextLevelView.update(deltaTime);
            nextLevelView.render();
            break;

        case ViewType::gameplay:
            if (lastView != currentView) {
                lastView = ViewType::gameplay;
            }
            if (stats.power >= powerLevelGoal) {
                stats.level++;
                powerLevelGoal += 6;
                mapManager->currentMap->initMap();
                currentView = ViewType::next_level;
                break;
            }
            gameplayView.handleInput();
            gameplayView.update(deltaTime);
            gameplayView.render();
            break;

        case ViewType::game_over:
            if (lastView != currentView) {
                player->currentPawnState = PawnState::die;
                lastView = ViewType::game_over;
            }
            gameOverView.update(deltaTime);
            gameOverView.render();
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

void Game::resetGameplay() {
    player->pos_x = 480;
    player->pos_y = Game::height - 48 * 2.5 + 24;
    stats.initBasicValues();
    stats.gameClock.restart();
    stats.totalElapsedTime = sf::Time::Zero;
    stats.allBreaksElapsedTime = sf::Time::Zero;
}
