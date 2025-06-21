#pragma once
#include <SFML/Graphics.hpp>
class Scene {
public:

    Scene() = default;
    virtual ~Scene() = default;

    virtual void handleEvent(sf::Event& event,sf::RenderWindow& window)=0;
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void checkInactivity(float elapsedTime) = 0;
   // [[nodiscard]]float getTimeInScene() const { return timeInScene; }
  //  [[nodiscard]]virtual std::unique_ptr<Scene> clone() const = 0;
protected:
    float timeInScene = 0.0f;

};