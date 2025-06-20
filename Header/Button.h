#pragma once
#include <SFML/Graphics.hpp>
class Button {
public:
    sf::RectangleShape rect;
    sf::Text text;
    sf::Color normalColor = sf::Color(100, 100, 100);
    sf::Color hoverColor = sf::Color(150, 150, 150);
    sf::Color clickColor = sf::Color(200, 200, 200);

    Button(const std::string& btnText, const sf::Font& font, sf::Vector2f position, sf::Vector2f size);
    void update(const sf::RenderWindow& window);
    bool isClicked(const sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;
    Button() = default;
};