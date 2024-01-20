#include "../../../Header Files/pawns/Enemy.hpp"
#include "../../../Header Files/pawns/enemies/Snake.hpp"


Enemy::Enemy() : Pawn() {
}

void Enemy::update(float deltaTime, bool moveable) { //all enemies
    for (auto& enemy : allEnemies) {
        enemy->update(deltaTime, enemy->moveable);
    }
}

void Enemy::render(sf::RenderTarget &target) { //all enemies
    for (auto& enemy : allEnemies) {
        enemy->render(target);
    }
}

void Enemy::initPawn() { //random enemy
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomValue = std::rand() % 1;

    switch (randomValue) {
        case 0: {
            type = EnemyType::snake;
            Snake* snake = new Snake();
            allEnemies.push_back(snake);
        }
        default:
            break;
    }
}

void Enemy::initAnimations() {
//none
}

void Enemy::updateAnimations(float d) {
    //none
}