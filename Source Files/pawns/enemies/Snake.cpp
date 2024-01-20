#include "../../../Header Files/pawns/enemies/Snake.hpp"

Snake::Snake() : Enemy() {
    init();
    initAnimations();
}

void Snake::init() {
    width = 32;
    height = 32;

    pos_x = (3 * 16 * 20) / 4; //[random]
    pos_y = 624 - 48 * 2.5 + 24;

    movementSpeed = 600.f;
    scale = 3.f;

    direction = Direction::right;
    lastPawnState = PawnState::idle;
    currentPawnState = PawnState::idle;

    isJumping = false;
    isFalling = true;
    moveable = true;

    sprite.setScale(scale, scale);
    characterFolder="snake";
}

void Snake::initAnimations() {
    run = Animation("../assets/enemies/" + characterFolder + "/Run.png", 6, scale, PawnState::run);
    death = Animation("../assets/enemies/" + characterFolder + "/Death.png", 8, scale, PawnState::die);
    hurt = Animation("../assets/enemies/" + characterFolder + "/Hurt.png", 4, scale, PawnState::hurt);
    attack = Animation("../assets/enemies/" + characterFolder + "/Attack.png", 4, scale, PawnState::directAttack);
}

void Snake::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(pos_x, pos_y - 24);
    target.draw(sprite);
}

void Snake::update(float deltaTime, bool moveable) {
    updateAnimations(deltaTime);
}

void Snake::updateAnimations(float deltaTime) {

    if (lastPawnState == PawnState::hurt) {
        std::cout<<hurt.lastPlayedFrameIndex<<std::endl;
        if (hurt.lastPlayedFrameIndex != 1) {
            currentPawnState = PawnState::hurt;
            sprite = hurt.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::hurt);
            return;
        }
    }

    switch (currentPawnState) {
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