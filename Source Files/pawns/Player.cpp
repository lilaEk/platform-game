#include "../../Header Files/pawns/Player.hpp"
#include "../../Header Files/Game.hpp"

Player::Player(PlayerChoice playerChoice) : Pawn() {
    chosenPlayer = playerChoice;

    initPlayer();
    initAnimations();
}

Player::~Player() = default;

void Player::initPlayer() {

    width = 32;
    height = 32;

    pos_x = (3 * 16 * 20) / 2;
    pos_y = Game::height - 48 * 2.5 + 24;

    movementSpeed = 600.f;
    scale = 3.f;

    direction = Direction::right;
    lastPawnState = PawnState::idle;
    currentPawnState = PawnState::idle;

    isJumping = false;
    isFalling = true;

    sprite.setScale(scale, scale);
}

void Player::initAnimations() {

    std::string characterFolder;
    switch (chosenPlayer) {
        case PlayerChoice::Dude_Monster:
            characterFolder = "Dude_Monster";
            break;
        case PlayerChoice::Owlet_Monster:
            characterFolder = "Owlet_Monster";
            break;
        default:
            characterFolder = "Pink_Monster";
            break;
    }

    idle = Animation("../assets/player/" + characterFolder + "/Idle.png", 4, scale, &lastPawnState);
    run = Animation("../assets/player/" + characterFolder + "/Run.png", 6, scale, &lastPawnState);
    jump = Animation("../assets/player/" + characterFolder + "/Jump.png", 8, scale, &lastPawnState);
    death = Animation("../assets/player/" + characterFolder + "/Death.png", 8, scale, &lastPawnState);
    roll = Animation("../assets/player/" + characterFolder + "/Roll.png", 6, scale, &lastPawnState);
    squat = Animation("../assets/player/" + characterFolder + "/Squat.png", 4, scale, &lastPawnState);
    happy = Animation("../assets/player/" + characterFolder + "/Happy.png", 6, scale, &lastPawnState);
    push = Animation("../assets/player/" + characterFolder + "/Push.png", 6, scale, &lastPawnState);
    climb = Animation("../assets/player/" + characterFolder + "/Climb.png", 6, scale, &lastPawnState);
    lift = Animation("../assets/player/" + characterFolder + "/Lift.png", 6, scale, &lastPawnState);
    hurt = Animation("../assets/player/" + characterFolder + "/Hurt.png", 4, scale, &lastPawnState);
    directAttack = Animation("../assets/player/" + characterFolder + "/Attack.png", 4, scale, &lastPawnState);
    directDoubleAttack = Animation("../assets/player/" + characterFolder + "/Attack_Double.png", 6, scale,
                                   &lastPawnState);
    throwAttack = Animation("../assets/player/" + characterFolder + "/Throw.png", 4, scale, &lastPawnState);
}

void Player::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(pos_x, pos_y - 24);
    target.draw(sprite);
}

void Player::update(float currentTime, bool moveable) {
    updateAnimations(currentTime);
}

void Player::updateAnimations(float deltaTime) {

    if (lastPawnState == PawnState::hurt) {
        std::cout<<hurt.lastPlayedFrameIndex<<std::endl;
        if (hurt.lastPlayedFrameIndex != 3) {
            currentPawnState = PawnState::hurt;
            sprite = hurt.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::hurt);
            return;
        }
    }

    switch (currentPawnState) {
        case PawnState::run:
            sprite = run.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::run);
            break;
        case ::PawnState::jump:
            sprite = jump.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::jump);
            break;
        case ::PawnState::die:
            sprite = death.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::die);
            break;
        case ::PawnState::roll:

            sprite = roll.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::roll);
            break;
        case ::PawnState::squat:
            sprite = squat.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::squat);
            break;
        case ::PawnState::happy:
            sprite = happy.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::happy);
            break;
        case ::PawnState::push:
            sprite = push.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::push);
            break;
        case ::PawnState::lift:
            sprite = lift.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::lift);
            break;
        case ::PawnState::hurt:
            sprite = hurt.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::hurt);
            break;
//        case fly:
//            break;
//        case ::pic:
//            break;
//        case ::directAttack:
//
//            sprite = directAttack.getCurrentAnimImg(
//            width,
//            height,
//            direction,
//            scale);
//            break;
        case ::PawnState::directDoubleAttack:
            sprite = directDoubleAttack.getCurrentAnimImg(deltaTime, width, height, direction, scale,
                                                          PawnState::directDoubleAttack);
            break;
        case ::PawnState::throwAttack:
            sprite = throwAttack.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::throwAttack);
            break;
        default: //idle
            sprite = idle.getCurrentAnimImg(deltaTime, width, height, direction, scale, PawnState::idle);
            break;
    }
}
