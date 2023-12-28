#include "../Header Files/Game.hpp"

//inits
void Game::initWindow() {
    this->vm.height = Game::height;
    this->vm.width = Game::width;

    this->window.create(this->vm, "my game", Style::Titlebar | Style::Close);
//    this->window.create(sf::VideoMode::getFullscreenModes()[0],"my game",sf::Style::Fullscreen);
}

void Game::initMap() {
this->mapManager = new MapManager();
}

void Game::initPlayer() {
    this->player = new Player();
}

Game::Game() {
    this->initWindow();
    this->initMap();
    this->initPlayer();
}

Game::~Game() {
    delete this->player;
    delete this->mapManager;
}

//accessors
const bool Game::running() const {
    return this->window.isOpen();
}

//functions
void Game::pollEvents() {

    while (this->window.pollEvent(this->e)) {
        switch (this->e.type) {
            //mouse click, keyboard, data
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

void Game::updateMap(float deltaTime){
    this->mapManager->update(deltaTime);
}

void Game::updatePlayer(float deltaTime) {
    this->player->update(deltaTime);
}

void Game::update(float deltaTime) {
    this->pollEvents();
    this->updateMap(deltaTime);
    this->updatePlayer(deltaTime);
}

void Game::renderPlayer() {
    this->player->render(this->window);
}

void Game::renderMap(){
    this->mapManager->render(this->window);
}

void Game::render() {
    //clear old frame
    //render objects
    //display frame in window

    this->window.clear(Color(255, 153, 204));

    //draw game
    this->drawBackgroundImage(this->window);
    this->renderMap();
    this->renderPlayer();

    this->window.display();
}

const RenderWindow &Game::getWindow() const {
    //insert return statement here
    return this->window;
}

void Game::drawBackgroundImage(RenderWindow &window) {

    sf::Texture bg1, bg2, bg3, bg5, bg8, bg10;

    if (!bg1.loadFromFile("../assets/background/1.png") ||
        !bg2.loadFromFile("../assets/background/2.png") ||
        !bg3.loadFromFile("../assets/background/3.png") ||
        !bg5.loadFromFile("../assets/background/5.png") ||
        !bg8.loadFromFile("../assets/background/8.png")
//        !bg10.loadFromFile("../assets/background/10.png")
            ) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    sf::Sprite background1(bg1);
    sf::Sprite background2(bg2);
    sf::Sprite background3(bg3);
    sf::Sprite background5(bg5);
    sf::Sprite background8(bg8);
//    sf::Sprite background10(bg10);

    float ratio1 = static_cast<float>(bg1.getSize().x) / bg1.getSize().y;
    float ratio2 = static_cast<float>(bg2.getSize().x) / bg2.getSize().y;
    float ratio3 = static_cast<float>(bg3.getSize().x) / bg3.getSize().y;
    float ratio5 = static_cast<float>(bg5.getSize().x) / bg5.getSize().y;
    float ratio8 = static_cast<float>(bg8.getSize().x) / bg8.getSize().y;
//    float ratio10 = static_cast<float>(bg10.getSize().x) / bg10.getSize().y;

    float minRatio = std::min({ratio1, ratio2, ratio3, ratio5, ratio8});

    background1.setScale(minRatio, minRatio);
    background2.setScale(minRatio, minRatio);
    background3.setScale(minRatio, minRatio);
    background5.setScale(minRatio, minRatio);
    background8.setScale(minRatio, minRatio);
//    background10.setScale(minRatio, minRatio);

//    background10.setPosition(0,70);

    window.draw(background1);
    window.draw(background2);
    window.draw(background3);
    window.draw(background5);
    window.draw(background8);
//    window.draw(background10);

}
