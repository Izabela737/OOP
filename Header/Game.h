#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Header/Scene.h"
#include "../Header/GameLogic.h"
#include <SFML/Audio.hpp>


class Game {
    sf::RenderWindow window;
    sf::Music backgroundMusic;
    std::unique_ptr<Scene> currentScene;
    GameLogic gameLogic;
    std::string playerName;

public:
    Game();
    ~Game();
    void initializeWindow();
    void changeScene(std::unique_ptr<Scene> newScene);
    void run();
};
