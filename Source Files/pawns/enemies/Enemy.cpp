#include "../../../Header Files/pawns/Enemy.hpp"
#include "../../../Header Files/pawns/enemies/Snake.hpp"
#include "../../../Header Files/pawns/enemies/ForestBoss.hpp"


Enemy::Enemy() : Pawn() {
}

void Enemy::update(float deltaTime, bool moveable) { //all enemies
    for (auto &enemy: allEnemies) {
        enemy->update(deltaTime, enemy->moveable);
        enemy->moveEnemy(deltaTime);
    }
}

void Enemy::render(sf::RenderTarget &target) { //all enemies
    for (auto &enemy: allEnemies) {
        enemy->render(target);
    }
}

void Enemy::initPawn() {
}

void Enemy::initPawn(int x) { //snake enemy

    type = EnemyType::snake;
    Snake *snake = new Snake();
    snake->pos_x = x;
    allEnemies.push_back(snake);

}

void Enemy::initForestBoss(int x) { //random enemy
    type = EnemyType::forest_boss;
    ForestBoss *forestBoss = new ForestBoss();
    forestBoss->pos_x = x;
    allEnemies.push_back(forestBoss);
}

void Enemy::initAnimations() {
//none
}

void Enemy::updateAnimations(float d) {
    //none
}

void Enemy::moveEnemy(float currentTime) {
    float moveSpeed = 100.0f;

    if (direction == Direction::left) {
        if (distance >= -100.0f) {
            distance -= currentTime * moveSpeed;
            pos_x += currentTime * moveSpeed;
        } else {
            distance = 0;
            direction = Direction::right;
        }
    } else if (direction == Direction::right) {
        if (distance <= 100.0f) {
            distance += currentTime * moveSpeed;
            pos_x -= currentTime * moveSpeed;
        } else {
            distance = 0;
            direction = Direction::left;
        }
    }

    sprite.setPosition(pos_x, pos_y);
}
