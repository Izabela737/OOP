#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class SceneManager {

    std::unique_ptr<Scene> currentScene;
public:
    void changeScene(std::unique_ptr<Scene> newScene);
    void handleEvent(sf::Event& event,sf::RenderWindow& window);
    void update(float deltaTime, sf::RenderWindow& window) ;
    void draw(sf::RenderWindow& window) ;
};
