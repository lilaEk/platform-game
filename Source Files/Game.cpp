#include "../Header Files/Game.hpp"

//inits
void Game::initWindow() {
    this->vm.height = Game::height;
    this->vm.width = Game::width;

    this->window.create(this->vm, "my game", Style::Titlebar | Style::Close);
//    this->window.create(sf::VideoMode::getFullscreenModes()[0],"my game",sf::Style::Fullscreen);
}

void Game::initPlayer() {
    this->player = new Player();
}


//constructor / destructor
Game::Game() {
    this->initWindow();
    this->initPlayer();
}

Game::~Game() {
    delete this->player;
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

void Game::update(float deltaTime) {
    this->pollEvents();
    this->updatePlayer(deltaTime);
}

void Game::updatePlayer(float deltaTime) {
    this->player->update(deltaTime);
}

void Game::renderPlayer() {
    this->player->render(this->window);
}


void Game::render() {
    //clear old frame
    //render objects
    //display frame in window

    this->window.clear(Color(255, 153, 204));

    //draw game
    this->drawBackgroundImage(this->window);
    this->renderPlayer();

    this->window.display();
}

const RenderWindow &Game::getWindow() const {
    //insert return statement here
    return this->window;
}

void Game::drawBackgroundImage(RenderWindow &window) {

    sf::Texture bg1, bg2, bg3, bg5, bg8;

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
