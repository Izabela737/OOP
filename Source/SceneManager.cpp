#include "../Header/SceneManager.h"
#include <memory>


void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
}
void SceneManager::handleEvent(sf::Event& event,sf::RenderWindow& window) {
    if (currentScene) {
        currentScene->handleEvent(event, window);
    }
}
void SceneManager::update(float deltaTime, sf::RenderWindow& window) {
    if (currentScene) {
        currentScene->update(deltaTime, window);
    }
    currentScene->checkInactivity(deltaTime);
}
void SceneManager::draw(sf::RenderWindow& window) {
    if (currentScene) {
        currentScene->draw(window);
    }
}
