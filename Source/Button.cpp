#include "../Header/Button.h"
#include <SFML/Graphics.hpp>


   Button::Button(const std::string& btnText, const sf::Font& font, const sf::Vector2f position, const sf::Vector2f size) {
        rect.setSize(size);
        rect.setPosition(position);
        rect.setFillColor(normalColor);

        text.setString(btnText);
        text.setFont(font);
        text.setCharacterSize(24);
        text.setPosition(
            position.x + (size.x - text.getLocalBounds().width) / 2,
            position.y + (size.y - text.getLocalBounds().height) / 2 - 5
        );
    }

   void Button::update(const sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (rect.getGlobalBounds().contains(mousePos)) {
            rect.setFillColor(hoverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                rect.setFillColor(clickColor);
            }
        } else {
            rect.setFillColor(normalColor);
        }
    }
   bool Button::isClicked(const sf::RenderWindow& window) const
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return rect.getGlobalBounds().contains(mousePos) &&
               sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    void Button::draw(sf::RenderWindow& window) const
    {
        window.draw(rect);
        window.draw(text);
    }
