#include "../../../Header Files/pawns/enemies/Snake.hpp"

Snake::Snake() : Enemy() {
    init();
    initAnimations();
    allEnemies.push_back(this);
}

void Snake::init() {
    width = 48;
    height = 48;

    pos_x = 0; //random
    pos_y = 488;

    movementSpeed = 0.f;
    scale = 3.f;

    direction = Direction::right;
    lastPawnState = PawnState::idle;
    currentPawnState = PawnState::idle;

    isJumping = false;
    isFalling = true;
    moveable = true;

    sprite.setScale(scale, scale);
    characterFolder="snake";

    currentPawnState=PawnState::run;
}

void Snake::initAnimations() {
    run = Animation("../assets/enemies/" + characterFolder + "/Run.png", 4, scale, PawnState::run);
    death = Animation("../assets/enemies/" + characterFolder + "/Death.png", 4, scale, PawnState::die);
    hurt = Animation("../assets/enemies/" + characterFolder + "/Hurt.png", 2, scale, PawnState::hurt);
    attack = Animation("../assets/enemies/" + characterFolder + "/Attack.png", 6, scale, PawnState::directAttack);
}

void Snake::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(pos_x, pos_y);
    target.draw(sprite);

}

void Snake::update(float deltaTime, bool moveable) {
    updateAnimations(deltaTime);
}

void Snake::updateAnimations(float deltaTime) {

    if (lastPawnState == PawnState::hurt) {

        if (hurt.lastPlayedFrameIndex != 1) {
            currentPawnState = PawnState::hurt;
            sprite = hurt.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::hurt);
            return;
        }
    }

    switch (currentPawnState) {
        case ::PawnState::run:
            sprite = run.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::idle);
            break;
        case ::PawnState::die:
            sprite = death.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::die);
            break;
        case ::PawnState::hurt:
            sprite = hurt.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::hurt);
            break;
        case ::PawnState::directAttack:
            sprite = attack.getCurrentAnimImg(deltaTime, width, height, direction, scale,PawnState::directDoubleAttack);
            break;
        default: //run
            sprite = run.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::idle);
            break;
    }
}