#include "../../Header Files/pawns/Player.hpp"
#include "../../Header Files/Game.hpp"

Player::Player(PlayerChoice playerChoice) : Pawn() {
    this->chosenPlayer=playerChoice;
    this->initPlayer();
    this->initAnimations();
}

Player::~Player() = default;

void Player::initPlayer() {
    this->width = 32;
    this->height = 32;

    this->pos_x = (3 * 16 * 20) / 2;
    this->pos_y = 450.f;

    this->movement_speed = 350.f;
    this->scale = 3.f;

    this->direction = Direction::right;
    this->lastPawnState = PawnState::idle;
    this->currentPawnState = PawnState::idle;
    this->isJumping = false;
    this->sprite.setScale(scale, scale);
}

void Player::initAnimations() {

    std::string characterFolder;
    switch (this->chosenPlayer) {
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

    this->idle = Animation("../assets/player/" + characterFolder + "/Idle.png", 4, scale, &this->lastPawnState);
    this->run = Animation("../assets/player/" + characterFolder + "/Run.png", 6, scale, &this->lastPawnState);
    this->jump = Animation("../assets/player/" + characterFolder + "/Jump.png", 8, scale, &this->lastPawnState);
    this->death = Animation("../assets/player/" + characterFolder + "/Death.png", 8, scale, &this->lastPawnState);
    this->roll = Animation("../assets/player/" + characterFolder + "/Roll.png", 6, scale, &this->lastPawnState);
    this->squat = Animation("../assets/player/" + characterFolder + "/Squat.png", 4, scale, &this->lastPawnState);
    this->happy = Animation("../assets/player/" + characterFolder + "/Happy.png", 6, scale, &this->lastPawnState);
    this->push = Animation("../assets/player/" + characterFolder + "/Push.png", 6, scale, &this->lastPawnState);
    this->climb = Animation("../assets/player/" + characterFolder + "/Climb.png", 6, scale, &this->lastPawnState);
    this->lift = Animation("../assets/player/" + characterFolder + "/Lift.png", 6, scale, &this->lastPawnState);
    this->hurt = Animation("../assets/player/" + characterFolder + "/Hurt.png", 4, scale, &this->lastPawnState);
    this->directAttack = Animation("../assets/player/" + characterFolder + "/Attack.png", 4, scale,
                                   &this->lastPawnState);
    this->directDoubleAttack = Animation("../assets/player/" + characterFolder + "/Attack_Double.png", 6, scale,
                                         &this->lastPawnState);
    this->throwAttack = Animation("../assets/player/" + characterFolder + "/Throw.png", 4, scale, &this->lastPawnState);

}

void Player::render(sf::RenderTarget &target) {
    sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
    this->sprite.setPosition(this->pos_x, this->pos_y);
    target.draw(this->sprite);
}

void Player::update(float currentTime, bool moveable) {
//    if (moveable) {
//        this->updateMovement(currentTime);
//    }
    this->updateAnimations(currentTime);
}

//void Player::updateMovement(float currentTime) {
//    this->lastPawnState = this->currentPawnState;
//
//    //left movement
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
//        or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
//
//        this->pos_x -= movement_speed * currentTime;
//
//        if (this->pos_x < 0 + width) {
//            this->pos_x = 0 + width;
//        };
//        this->currentPawnState = PawnState::run;
//        if (this->direction == Direction::right) {
//            this->direction = Direction::left;
//        }
//    }
//        //right movement
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
//
//        if (this->pos_x<(3*16*20)/2) {
//            this->pos_x += movement_speed * currentTime;
//
//            if (this->pos_x > Game::width - width) {
//                this->pos_x = Game::width - width;
//            };
//        } else {
////            Game::scrollMap(movement_speed * currentTime);
//        }
//
//        this->currentPawnState = PawnState::run;
//        if (this->direction == Direction::left) {
//            this->direction = Direction::right;
//        }
//    }
//        //jump - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
//        this->pos_y -= 10.F;
//        if (this->pos_y < 30.f) {
//            this->pos_y = 30.f;
//        };
//        this->currentPawnState = PawnState::jump;
//    }
//        //roll / squat - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
//             or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
//        this->pos_y += 20.F;
//        if (this->pos_y > 450.f) {
//            this->pos_y = 450.f;
//        };
//        this->currentPawnState = PawnState::squat;
//    }
//        //directDoubleAttack - k - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
//        this->currentPawnState = PawnState::directDoubleAttack;
//    }
//        //throwAtack - l - todo
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
//        this->currentPawnState = PawnState::throwAttack;
//    }
//        //brak ruchu
//    else {
//        this->currentPawnState = PawnState::idle;
//    }
//}

void Player::updateAnimations(float deltaTime) {

    switch (this->currentPawnState) {
        case PawnState::run:
            this->sprite = run.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                 this->scale, PawnState::run);
            break;
        case ::PawnState::jump:
            this->sprite = jump.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::jump);
            break;
        case ::PawnState::die:
            this->sprite = death.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                   PawnState::die);
            break;
        case ::PawnState::roll:
            this->sprite = roll.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::roll);
            break;
        case ::PawnState::squat:
            this->sprite = squat.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                   PawnState::squat);
            break;
        case ::PawnState::happy:
            this->sprite = happy.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                   PawnState::happy);
            break;
        case ::PawnState::push:
            this->sprite = push.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::push);
            break;
        case ::PawnState::lift:
            this->sprite = lift.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::lift);
            break;
        case ::PawnState::hurt:
            this->sprite = hurt.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::hurt);
            break;
//        case fly:
//            break;
//        case ::pic:
//            break;
//        case ::directAttack:
//            this->sprite = directAttack.getCurrentAnimImg(this->width, this->height, this->direction, this->scale);
//            break;
        case ::PawnState::directDoubleAttack:
            this->sprite = directDoubleAttack.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                                this->scale, PawnState::directDoubleAttack);
            break;
        case ::PawnState::throwAttack:
            this->sprite = throwAttack.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction,
                                                         this->scale, PawnState::throwAttack);
            break;
        default: //idle
            this->sprite = idle.getCurrentAnimImg(deltaTime, this->width, this->height, this->direction, this->scale,
                                                  PawnState::idle);
            break;
    }
}