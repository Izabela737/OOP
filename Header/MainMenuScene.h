#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class MainMenuScene : public Scene {

    void initializeButtons();

    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Texture startButtonTexture;
    sf::Sprite startButtonSprite;
    sf::Texture exitButtonTexture;
    sf::Sprite exitButtonSprite;

    struct MenuButton {
        sf::Sprite sprite;
        sf::Texture texture;
        std::function<void()> action;

        void setPosition(float x, float y) {
            sprite.setPosition(x, y);
        }
        void draw(sf::RenderWindow& window) const
        {
            window.draw(sprite);
        }
    };
    std::vector<MenuButton> buttons;
    std::function<void(const std::string&)> startCallback;
public:
    MainMenuScene(sf::RenderWindow& window, std::function<void(const std::string&)> onStart);
    void handleEvent( sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void checkInactivity(float elapsedTime) override;
   // std::unique_ptr<Scene> clone() const override {
   //     return std::make_unique<MainMenuScene>(*this);
  // }
};