#include "../Header Files/Stats.hpp"

void Stats::initStats() {
    this->level = 1;
    this->points = 0;
    this->gameTime = 0;
    this->lives = 3;

    this->clock.restart();


    if (!this->heartTexture.loadFromFile("../assets/background/1.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    this->heart.setTexture(this->heartTexture);
}

void Stats::updateLevel() {}

void Stats::updatePoints() {}

void Stats::updateTime() {
    sf::Time elapsed = clock.getElapsedTime();
    getFormattedTime(elapsed);
}

void Stats::updateLives() {}

void Stats::updateStats() {
    updateLevel();
    updatePoints();
    updateTime();
    updateLives();
}

void Stats::getFormattedTime(sf::Time time) {

    int hours = static_cast<int>(time.asSeconds()) / 3600;
    int minutes = (static_cast<int>(time.asSeconds()) % 3600) / 60;
    int seconds = static_cast<int>(time.asSeconds()) % 60;


    if (hours > 0) {
        if (hours < 10)
            this->formattedTime = "0" + std::to_string(hours) + ':';
        else
            this->formattedTime = std::to_string(hours) + ':';
    }

    if (minutes == 0) {
        this->formattedTime += "00:";
    } else if (minutes < 10) {
        this->formattedTime += "0" + std::to_string(minutes) + ':';
    } else {
        this->formattedTime += std::to_string(minutes) + ':';
    }

    if (seconds == 0) {
        this->formattedTime += "00";
    } else if (seconds < 10) {
        this->formattedTime += "0" + std::to_string(seconds);
    } else {
        this->formattedTime += std::to_string(seconds);
    }
}

void Stats::render(sf::RenderTarget &target) {

}
