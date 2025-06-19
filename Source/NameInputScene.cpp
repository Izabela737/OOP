#include "../Header/NameInputScene.h"
#include <iostream>

NameInputScene::NameInputScene(sf::RenderWindow& window, std::function<void(const std::string&)> callback)
    : window_(window), onNameEntered(std::move(callback))
{
    if (!font.loadFromFile("fonts/geo.ttf")) {
    throw std::runtime_error("Eroare la incarcarea fontului!");
}
    warningText.setFont(font);
    warningText.setCharacterSize(24);
    warningText.setStyle(sf::Text::Bold);
    warningText.setFillColor(sf::Color::White);
    warningText.setString("");
    warningText.setPosition(-1000.f, -1000.f);

    if (!WTexture.loadFromFile("imagini/warning.png")) {
        throw std::runtime_error("Failed to load image");
    }
    WSprite.setTexture(WTexture);

    WSprite.setPosition(-1000.f, -1000.f);
    warningBackground.setFillColor(sf::Color(50, 50, 50, 180));
    warningBackground.setSize(sf::Vector2f(400.f, 120.f));
    warningBackground.setPosition(-1000.f, -1000.f);
    if (!backgroundTexture.loadFromFile("imagini/startmenu.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    backgroundSprite.setTexture(backgroundTexture);

    const sf::Vector2u textureSize = backgroundTexture.getSize();
    const sf::Vector2u windowSize = window.getSize();

    const float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    const float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);
    backgroundSprite.setScale(scaleX, scaleY);
    if (!inputTexture.loadFromFile("imagini/input.png"))
    {
        throw std::runtime_error("Failed to load input menu image");
    }
    shadowSprite.setColor(sf::Color(0, 0, 0, 200));
    shadowSprite.move(3.f, 3.f);
    inputSprite.setTexture(inputTexture);
    inputSprite.setScale(2.f, 2.f);

    const sf::FloatRect bounds = inputSprite.getGlobalBounds();

    float x = (static_cast<float>(windowSize.x) - bounds.width) / 2.f;
    float y = (static_cast<float>(windowSize.y) - bounds.height) / 2.f;

    inputSprite.setPosition(x, y);
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);

    inputBox.setSize(sf::Vector2f(250.f, 50.f));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2.f);

    const sf::FloatRect inputBounds = inputSprite.getGlobalBounds();

    constexpr float paddingX = 250.f;
    constexpr float paddingY = 127.f;
    inputBox.setPosition(inputBounds.left + paddingX, inputBounds.top + paddingY);
    inputText.setPosition(inputBounds.left + paddingX, inputBounds.top + paddingY);
}

void NameInputScene::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::Closed) {
        window.close();
        return;
    }
    if (event.type == sf::Event::TextEntered) {
        bool hasTyped = false;

        if (event.text.unicode == '\b') {
            if (!playerName.empty()) {
                playerName.pop_back();
                hasTyped = true;
            }
        } else if (event.text.unicode == '\r') {
            if (!playerName.empty()) {
                try {
                    onNameEntered(playerName);
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la callback: " << e.what() << "\n";
                } catch (...) {
                    std::cerr << "Eroare necunoscută la callback!\n";
                }
            }
        } else if (event.text.unicode < 128 && std::isprint(static_cast<char>(event.text.unicode))) {
            if (playerName.size() < maxLength) {
                playerName += static_cast<char>(event.text.unicode);
                hasTyped = true;
            }
        }
        inputText.setString(playerName);
        if (hasTyped) {
            warningShown = false;
            warningText.setString("");
            warningBackground.setPosition(-1000.f, -1000.f);
            warningText.setPosition(-1000.f, -1000.f);
            WSprite.setPosition(-1000.f, -1000.f);
            timeInScene = 0.f;
        }
    }
}
void NameInputScene::update(const float deltaTime, sf::RenderWindow& window) {
    timeInScene += deltaTime;
    checkInactivity(deltaTime);
    (void)window;
}
void NameInputScene::draw(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite);
    window.draw(shadowSprite);
    window.draw(inputSprite);
    window.draw(inputText);
    if (warningShown) {
        window.draw(warningBackground);
        window.draw(WSprite);
        window.draw(warningText);
    }else  ;
}
void NameInputScene::checkInactivity(const float elapsedTime)
{
    (void)elapsedTime;
    if (timeInScene > 5.f && !warningShown) {
        const sf::Vector2u windowSize = window_.getSize();
        warningText.setString("This is the most important decision you'll make today. No pressure.");
        const float iconX = (static_cast<float>(windowSize.x) - WSprite.getGlobalBounds().width) / 2.f;
        const float iconY = static_cast<float>(windowSize.y) / 2.f - 300.f;
        WSprite.setPosition(iconX, iconY);
        const sf::FloatRect imageBounds = WSprite.getGlobalBounds();
        constexpr float padding = 10.f;
        const sf::FloatRect textBounds = warningText.getLocalBounds();
        const float textX = imageBounds.left + (imageBounds.width - textBounds.width) / 2.f;
        const float textY = imageBounds.top + imageBounds.height + 10.f;
        warningText.setPosition(textX, textY);
        warningBackground.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
        warningBackground.setFillColor(sf::Color(0, 0, 0, 100));
        warningBackground.setOrigin(warningBackground.getSize().x / 2.f, warningBackground.getSize().y / 2.f);
        warningBackground.setPosition(
            textX + textBounds.width / 2.f,
            textY + textBounds.height / 2.f
        );
        warningShown = true;
    }
}
