#include "../Header Files/Game.hpp"

Game::Game() : player(new Player(PlayerChoice::Dude_Monster)),
               mapManager(new MapManager),
               window(sf::VideoMode(Game::width, Game::height), "platform game by rozalia",
                      sf::Style::Titlebar | sf::Style::Close),
               mainMenuView(*mapManager, player, window, &stats),
               gameplayView(*mapManager, player, window, &stats),
               nextLevelView(*mapManager, player, window, &stats),
               gameOverView(*mapManager, player, window, &stats) {

    view.setSize(static_cast<float>(Game::width), static_cast<float>(Game::height));
    view.setCenter(static_cast<float>(Game::width) / 2.f, static_cast<float>(Game::height) / 2.f);
    window.setView(view);

    currentView = ViewType::main_menu;
    lastView = ViewType::main_menu;

    nick = "";

    mainMenuView.setStartButtonCallback([this] {
        if (nick.empty()) {
            nick = mainMenuView.nick;
        }
        currentView = ViewType::next_level;
    });
    generateRanking();
}

Game::~Game() {
    delete player;
    delete mapManager;
}

bool Game::running() const {
    return window.isOpen();
}

void Game::pollEvents() {

    while (window.pollEvent(e)) {
        switch (e.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (e.key.code == Keyboard::Escape &&
                    (currentView == ViewType::next_level || currentView == ViewType::game_over)) {
                    currentView = ViewType::main_menu;
                } else if (e.key.code == sf::Keyboard::Enter && currentView == ViewType::next_level) {
                    currentView = ViewType::gameplay;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (currentView == ViewType::main_menu) {
                    if (e.mouseButton.button == sf::Mouse::Left) {
                        handleMouseClick(e.mouseButton.x, e.mouseButton.y);
                        stats.gameClock.restart();
                        stats.totalElapsedTime = sf::Time::Zero;
                        stats.allBreaksElapsedTime = sf::Time::Zero;
                        stats.inBreak = false;
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (currentView == ViewType::main_menu) {
                    mainMenuView.handleTextEntered(e);
                    nick=mainMenuView.playerNick.getText();

                    std::replace_if(nick.begin(), nick.end(), [](char c) {
                        return std::isspace(static_cast<unsigned char>(c));
                    }, '_');
                }
                break;
        }
    }
}

void Game::update_and_render(float deltaTime) {
    pollEvents();

    window.clear();
    window.setView(view);

    drawBackgroundImage(window);

    if (stats.lives < 0.5 && currentView == ViewType::gameplay) {
        currentView = ViewType::game_over;
    }

    stats.updateStats(currentView);

    switch (currentView) {
        case ViewType::main_menu:

            if (lastView != currentView) {
                if (lastView != ViewType::next_level) { mapManager->currentMap->initMap(); }
                player->currentPawnState = PawnState::idle;
                resetGameplay();
                lastView = ViewType::main_menu;
                generateRanking();
            }
            mainMenuView.update(deltaTime, playerData);
            mainMenuView.render();
            break;

        case ViewType::next_level:

            if (lastView != currentView) {
                saveStatsToCSV("../game_saves/" + nick + "_save.csv");
                generateRanking();

                player->currentPawnState = PawnState::happy;
                lastView = ViewType::next_level;

                player->pos_x = 480;
                player->pos_y = Game::height - 48 * 2.5 + 24;

                if (stats.level != 1) {
                    mapManager->currentMap->initMap();
                }
                stats.breakClock.restart();
            }
            nextLevelView.update(deltaTime);
            nextLevelView.render();
            break;

        case ViewType::gameplay:
            if (lastView != currentView) {
                lastView = ViewType::gameplay;
                if (stats.power < 20) {
                    powerLevelGoal = 20;
                } else {
                    powerLevelGoal = ((stats.power + 9) / 10) * 10;
                }
            }
            if (stats.power >= powerLevelGoal) {
                stats.level++;
                powerLevelGoal += 10;
                mapManager->currentMap->initMap();
                currentView = ViewType::next_level;
                break;
            }
            gameplayView.handleInput();
            gameplayView.update(deltaTime);
            gameplayView.render();
            break;

        case ViewType::game_over:
            if (lastView != currentView) {
                player->currentPawnState = PawnState::die;
                lastView = ViewType::game_over;
            }
            gameOverView.update(deltaTime);
            gameOverView.render();
            break;
    }

    window.display();
}

const RenderWindow &Game::getWindow() const {
    return window;
}

void Game::drawBackgroundImage(RenderWindow &window) {

    sf::Texture bg1, bg2, bg3, bg5, bg8, bg10;

    if (!bg1.loadFromFile("../assets/background/1.png") ||
        !bg2.loadFromFile("../assets/background/2.png") ||
        !bg3.loadFromFile("../assets/background/3.png") ||
        !bg5.loadFromFile("../assets/background/5.png") ||
        !bg8.loadFromFile("../assets/background/8.png")
            ) {
        std::cout << "ERROR: Could not load texture from file\n";
    }

    sf::Sprite background1(bg1);
    sf::Sprite background2(bg2);
    sf::Sprite background3(bg3);
    sf::Sprite background5(bg5);
    sf::Sprite background8(bg8);

    float scaleX = static_cast<float>(window.getSize().x) / bg1.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / bg1.getSize().y;

    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    background3.setScale(scaleX, scaleY);
    background5.setScale(scaleX, scaleY);
    background8.setScale(scaleX, scaleY);

    window.draw(background1);
    window.draw(background2);
    window.draw(background3);
    window.draw(background5);
    window.draw(background8);
}

void Game::handleMouseClick(int mouseX, int mouseY) {
    switch (currentView) { //todo do uzupełnienia
        case ViewType::main_menu:
            mainMenuView.handleButtonClick(mouseX, mouseY);
            break;
        default:
            break;
    }
}

void Game::resetGameplay() {
    player->pos_x = 480;
    player->pos_y = Game::height - 48 * 2.5 + 24;
    stats.initBasicValues();
    stats.gameClock.restart();
    stats.totalElapsedTime = sf::Time::Zero;
    stats.allBreaksElapsedTime = sf::Time::Zero;
}

void Game::saveStatsToCSV(const std::string &filename) {
    std::ofstream outputFile(filename);
    outputFile.clear();

    if (outputFile.is_open()) {
        outputFile << "name,level,power,points,lives,time\n";

        outputFile << nick << ","
                   << stats.level << ","
                   << stats.power << ","
                   << stats.points << ","
                   << stats.lives << ","
                   << stats.formattedTime << "\n";
        outputFile.flush();
        outputFile.close();
    } else {
        std::cout << "ERROR: Could not open file for writing: " << filename << std::endl;
    }
}

//void Game::loadStatsFromCSV(const std::string &filename) {
//    std::ifstream inputFile(filename);
//    if (inputFile.is_open()) {
//        std::string header;
//        std::getline(inputFile, header);
//
//        inputFile >> stats.level;
//        inputFile.ignore();
//        inputFile >> stats.power;
//        inputFile.ignore();
//        inputFile >> stats.points;
//        inputFile.ignore();
//        inputFile >> stats.lives;
//        inputFile.ignore();
//        std::getline(inputFile, stats.formattedTime);
//
//        inputFile.close();
//    } else {
//        std::cout << "ERROR: Could not open file for reading: " << filename << std::endl;
//    }
//}

void Game::generateRanking() {

    playerData.clear();
    std::ofstream rankingFile("../ranking.csv");

    if (rankingFile.is_open()) {
        rankingFile << "Rank,PlayerName,Level,Power,Points,Lives,Time\n";

        for (const auto &entry: std::filesystem::directory_iterator("../game_saves")) {
            if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                processFile(entry);
            }
        }

        std::sort(playerData.begin(), playerData.end(), [](const auto &a, const auto &b) {
            return std::get<3>(a) > std::get<3>(b);
        });

        for (size_t i = 0; i < playerData.size(); ++i) {
            rankingFile << i + 1 << ","
                        << std::get<0>(playerData[i]) << ","
                        << std::get<1>(playerData[i]) << ","
                        << std::get<2>(playerData[i]) << ","
                        << std::get<3>(playerData[i]) << ","
                        << std::get<4>(playerData[i]) << ","
                        << std::get<5>(playerData[i]) << "\n";
        }
        rankingFile.flush();
        rankingFile.close();
    } else {
        std::cerr << "ERROR: Could not open file for writing: ../ranking.csv" << std::endl;
    }
}

void Game::processFile(const std::filesystem::directory_entry &entry) {
    std::string filePath = entry.path().string();
    std::replace(filePath.begin(), filePath.end(), '\\', '/');

    std::ifstream inputFile(filePath);

    if (inputFile.is_open()) {
        std::string playerName;
        int level, power, points;
        double lives;
        std::string time;

        std::string line;
        if (std::getline(inputFile, line)) {
            while (std::getline(inputFile, line)) {
                std::istringstream iss(line);
                char comma;

                if (std::getline(iss, playerName, ',') &&
                    iss >> level >> comma >> power >> comma >> points >> comma >> lives >> comma >> time) {

                    playerData.emplace_back(playerName, level, power, points, lives, time);
                } else {
                    std::cerr << "ERROR: Failed to read data from file: " << filePath << std::endl;
                    continue;
                }
            }
        } else {
            std::cerr << "ERROR: Empty file or failed to read header: " << filePath << std::endl;
        }

        inputFile.close();
    } else {
        std::cerr << "ERROR: Could not open file for reading: " << filePath << std::endl;
    }
}