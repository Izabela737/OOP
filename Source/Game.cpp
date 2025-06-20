#include "../Header/Game.h"
#include "../Header/MainMenuScene.h"
#include "../Header/NameInputScene.h"
#include "../Header/GameScene.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "The Journey Home", sf::Style::Titlebar | sf::Style::Close),
        currentScene(nullptr),
        gameLogic("")
{
    initializeWindow();
    if (!backgroundMusic.openFromFile("sound/backgroundM.mp3")) {
        std::cerr << "Nu s-a putut încărca muzica!" << std::endl;
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50.f);
        backgroundMusic.play();
    }
    currentScene = std::make_unique<MainMenuScene>(window, [this](const std::string& ) {

        changeScene(std::make_unique<NameInputScene>(window, [this](const std::string& name) {
            playerName = name;
            gameLogic = GameLogic(playerName);
            changeScene(std::make_unique<GameScene>(gameLogic,window));
        }));
    });
}
void Game::initializeWindow()
{
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
}
void Game::changeScene(std::unique_ptr<Scene> newScene)
{
    if (newScene) {
        currentScene = std::move(newScene);
    } else {
        std::cerr << "Eroare: încercare de a schimba către o scenă null.\n";
    }
}
void Game::run() {

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (currentScene)
                currentScene->handleEvent(event, window);
        }
        const float deltaTime = clock.restart().asSeconds();
        if (currentScene)
            currentScene->update(deltaTime, window);
        window.clear();
        if (currentScene)
            currentScene->draw(window);
        window.display();
    }
}
Game::~Game()
{
    backgroundMusic.stop();
}


