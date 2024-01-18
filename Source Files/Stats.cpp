#include <cmath>
#include "../Header Files/Stats.hpp"

void Stats::initStats() {
    this->level = 1;
    this->points = 0;
    this->power = 10;
    this->lives = 1.0;
    this->elapsedTime = sf::Time::Zero;

    this->formattedTime = getFormattedTime(elapsedTime);

    if (!font.loadFromFile("../assets/font/Planes_ValMore.ttf")) {
        std::cout << "ERROR: Could not load font from file\n";
    }

    if (!heartFull.loadFromFile("../assets/other_elements/hearts/heart_full.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    if (!heartHalf.loadFromFile("../assets/other_elements/hearts/heart_half.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }
    if (!heartEmpty.loadFromFile("../assets/other_elements/hearts/heart_empty.png")) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    statsBar.setSize(sf::Vector2f(540.f, 80.f));
    statsBar.setFillColor(sf::Color(0, 138, 182));

    texts.push_back(sf::Text("level", font, 20));
    texts.push_back(sf::Text("power", font, 20));
    texts.push_back(sf::Text("points", font, 20));
    texts.push_back(sf::Text("time", font, 20));
    texts.push_back(sf::Text("lives", font, 20));

    int x = 20;
    int y = 10;
    int breakBetween = 90;
    for (sf::Text &text: texts) {
        text.setPosition(x, y);
        text.setFillColor(sf::Color::Black);
        x += breakBetween;
    }

    stats.push_back(sf::Text(std::to_string(level), font, 20));
    stats.push_back(sf::Text(std::to_string(power), font, 20));
    stats.push_back(sf::Text(std::to_string(points), font, 20));
    stats.push_back(sf::Text(formattedTime, font, 20));

    x = 20;
    y = 40;
    for (sf::Text &stat: stats) {
        stat.setPosition(x, y);
        stat.setFillColor(sf::Color::Black);
        x += breakBetween;
    }
}

void Stats::updateLevel() {}

void Stats::updatePower() {
    stats[1].setString(std::to_string(power));
}

void Stats::updatePoints() {
    stats[2].setString(std::to_string(points));
}

void Stats::updateTime(sf::Clock& gameplayClock) {
    sf::Time elapsed = gameplayClock.getElapsedTime();
    sf::Time delta = elapsed - elapsedTime;

    formattedTime = getFormattedTime(elapsed);
    stats[3].setString(formattedTime);

    elapsedTime = elapsed;

}

void Stats::updateLives() {

    int fullHearts = static_cast<int>(lives);
    int halfHearts = std::round((lives - fullHearts) * 2);

    for (int i = 0; i < fullHearts; ++i) {
        hearts[i] = "full";
    }
    for (int i = fullHearts; i < fullHearts + halfHearts; ++i) {
        hearts[i] = "half";
    }
    for (int i = fullHearts + halfHearts; i < 5; ++i) {
        hearts[i] = "empty";
    }

    if (lives == 5) {
        texts[4].setString("lives (max)");
    } else {
        texts[4].setString("lives");
    }
}

void Stats::updateStats(sf::Clock& gameplayClock) {
    updateLevel();
    updatePower();
    updatePoints();
    updateTime(gameplayClock);
    updateLives();
}

std::string Stats::getFormattedTime(sf::Time time) {

    std::string newTime = "";
    int hours = static_cast<int>(time.asSeconds()) / 3600;
    int minutes = (static_cast<int>(time.asSeconds()) % 3600) / 60;
    int seconds = static_cast<int>(time.asSeconds()) % 60;


    if (hours > 0) {
        if (hours < 10)
            newTime += "0" + std::to_string(hours) + ':';
        else
            newTime += std::to_string(hours) + ':';
    }

    if (minutes == 0) {
        newTime += "00:";
    } else if (minutes < 10) {
        newTime += "0" + std::to_string(minutes) + ':';
    } else {
        newTime += std::to_string(minutes) + ':';
    }

    if (seconds == 0) {
        newTime += "00";
    } else if (seconds < 10) {
        newTime += "0" + std::to_string(seconds);
    } else {
        newTime += std::to_string(seconds);
    }

    return newTime;
}

void Stats::render(sf::RenderTarget &target) {

    target.draw(statsBar);

    for (sf::Text &text: texts) {
        target.draw(text);
    }
    for (sf::Text &stat: stats) {
        target.draw(stat);
    }

    renderHearts(target);
}

void Stats::renderHearts(sf::RenderTarget &target) {
    int x = 380;
    int y = 40;
    int breakBetween = 28;

    for (std::string heart: hearts) {
        if (heart == "full") {
            heartSprite.setTexture(heartFull);
            heartSprite.setPosition(x, y);
            heartSprite.setScale(0.5f, 0.5f);
            target.draw(heartSprite);
            x += breakBetween;
        }
        if (heart == "half") {
            heartSprite.setTexture(heartHalf);
            heartSprite.setPosition(x, y);
            heartSprite.setScale(0.5f, 0.5f);
            target.draw(heartSprite);
            x += breakBetween;
        }
        if (heart == "empty") {
            heartSprite.setTexture(heartEmpty);
            heartSprite.setPosition(x, y);
            heartSprite.setScale(0.5f, 0.5f);
            target.draw(heartSprite);
            x += breakBetween;
        }
    }
}

void Stats::addLive() {
    if (lives>=4.0){
        lives=5.0;
        return;
    }
    lives += 1;
}

void Stats::removeLive(double value) {
    if (lives>=value) {
        lives -= value;
        return;
    }
    lives=0;
}

void Stats::addPoints(int pointsToAdd) {
    this->points+=pointsToAdd;
}

void Stats::addPower(int powerPointsToAdd) {
    power+=powerPointsToAdd;
}