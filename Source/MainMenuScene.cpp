#include "../Header/MainMenuScene.h"
#include "../Header/NameInputScene.h"
#include <iostream>
MainMenuScene::MainMenuScene(sf::RenderWindow& window, std::function<void(const std::string&)> onStart)
    : window(window), startCallback(std::move(onStart))
{
    if (!backgroundTexture.loadFromFile("imagini/startmenu.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    backgroundSprite.setTexture(backgroundTexture);
    const sf::Vector2u textureSize = backgroundTexture.getSize();
    const sf::Vector2u windowSize = window.getSize();
    const float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    const float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);
    backgroundSprite.setScale(scaleX, scaleY);

    initializeButtons();
}
void MainMenuScene::initializeButtons()
{
    if (!startButtonTexture.loadFromFile("imagini/Bstart.png")) {
        throw std::runtime_error("Nu s-a putut încărca start_button.png");
    }
    startButtonSprite.setTexture(startButtonTexture);
    startButtonSprite.setScale(0.9f, 0.9f);
    const float startX = (static_cast<float>(window.getSize().x) - startButtonSprite.getGlobalBounds().width) / 2.f;
    constexpr float startY = 250.f;
    startButtonSprite.setPosition(startX, startY);

    if (!exitButtonTexture.loadFromFile("imagini/Bexit.png")) {
        throw std::runtime_error("Nu s-a putut încărca exit_button.png");
    }
    exitButtonSprite.setTexture(exitButtonTexture);
    exitButtonSprite.setScale(0.8f, 0.8f);
    const float exitX = (static_cast<float>(window.getSize().x) - exitButtonSprite.getGlobalBounds().width) / 2.f;
    constexpr float exitY = 370.f;
    exitButtonSprite.setPosition(exitX, exitY);
    buttons.clear();

    MenuButton startButton;
    startButton.sprite = startButtonSprite;
    startButton.texture = startButtonTexture;
    startButton.action = [this]() { startCallback(""); };
    buttons.push_back(startButton);

    MenuButton exitButton;
    exitButton.sprite = exitButtonSprite;
    exitButton.texture = exitButtonTexture;
    exitButton.action = [this]() {  window.close(); };
    buttons.push_back(exitButton);
}
void MainMenuScene::handleEvent( sf::Event& event, sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        for (auto& button : buttons)
        {
            if (button.sprite.getGlobalBounds().contains(mousePos)) {
                button.action();
                return;
            }
        }
    }
}
void MainMenuScene::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(startButtonSprite);
    window.draw(exitButtonSprite);
}
void MainMenuScene::update(float deltaTime, sf::RenderWindow& window)
{
     timeInScene += deltaTime;
    (void)window;
}
void MainMenuScene::checkInactivity(float elapsedTime) {
    static float inactivityTime = 0.f;
    inactivityTime += elapsedTime;
    if (inactivityTime > 1.f) {
        std::cout << "Inactiv de prea mult timp! Apasă Start!" << std::endl;
        inactivityTime = 0.f;
    }
}