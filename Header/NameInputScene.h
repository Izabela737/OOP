#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "../Header/Scene.h"

class NameInputScene : public Scene {

    sf::RenderWindow& window_;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture inputTexture;
    sf::Sprite inputSprite;
    sf::Sprite shadowSprite;
    sf::Texture WTexture;
    sf::Sprite WSprite;
    sf::Font font;
    sf::Text inputText;
    std::string playerName;
    std::function<void(const std::string&)> onNameEntered;
    sf::RectangleShape inputBox;
    sf::RectangleShape warningBackground;
    const size_t maxLength = 12;
    bool warningShown = false;
    sf::Text warningText;
public:
    NameInputScene(sf::RenderWindow& window, std::function<void(const std::string&)> callback);
    void checkInactivity(float elapsedTime) override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override ;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
   // std::unique_ptr<Scene> clone() const override {
    //    return std::make_unique<NameInputScene>(*this);
   // }
};
