#include "../Headers/Game.hpp"

//inits
void Game::initWindow() {
    this->vm.height = 600;
    this->vm.width = 1200;

    this->window.create(this->vm, "my game", Style::Titlebar | Style::Close);
//    this->window.create(sf::VideoMode::getFullscreenModes()[0],"my game",sf::Style::Fullscreen);
    this->window.setFramerateLimit(144);
}

void Game::initPlayer(){
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

    while (this->window.pollEvent(this->e)) { //jesli cos sie dzieje w oknie chcemy to zapisac w e
        switch (this->e.type) {
            //mouse click, keyboard, data
            case Event::Closed:
                this->window.close();
                break;
            case Event::KeyPressed:
                //do wyjebania
                if (e.key.code == Keyboard::Escape)
                    this->window.close();
                break;
        }
    }
}

void Game::update(float deltaTime) {
    this-> pollEvents();

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

    this->window.clear(Color(255,153,204));

    //draw game
    this->renderPlayer();

    this->window.display();
}

const RenderWindow &Game::getWindow() const {
    //insert return statement here
    return this->window;
}