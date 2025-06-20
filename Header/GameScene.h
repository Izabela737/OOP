#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

#include "Scene.h"
#include "GameLogic.h"
#include "Dinozaur.h"
#include "../Header/Button.h"

enum class GameState {
    Intro,
    IntroEncounter,
    Playing,
    Fighting,
    Waiting,
    GameOver,
    Victory
};

class GameScene : public Scene {
    GameLogic& gameLogic;
    sf::RenderWindow& window;

    GameState state = GameState::Intro;
    bool dataInitialized = false;
    bool canClick = false;
    bool isPlayerTurn = true;
    bool encounterStarted = false;
    bool isPaused = false;
    bool btnYesCreated = false;
    bool showHitMiss = false;
    float hitMissTimer = 0.f;
    float hitMissScale = 0.1f;
    float inactivityTime = 0.f;
    bool inactivityMessageShown = false;
    bool isTurnTransition = false;
    float introDuration = 1.5f;

    sf::Clock introClock, waitingClock, turnDelayClock;

    sf::Font font;
    sf::Text storyText, waitingText, mesajDialog, line1, line2, line3, line4, line5, turnText;

    sf::Texture backgroundTexture, waitTexture, endTexture, vicTexture, vicBackgroundTexture;
    sf::Texture playerTexture, dinoETexture, dinoCTexture, fundalTexture;
    sf::Texture hpBar0, hpBar25, hpBar50, hpBar75, hpBar100, HP;
    sf::Texture newGameButtonTexture, exitButtonTexture;
    sf::Texture texAtacSlab, texAtacPuternic;
    sf::Texture hitTexture, missTexture;

    sf::Sprite backgroundSprite, waitSprite, endSprite, vicSprite, vicBackgroundSprite;
    sf::Sprite playerSprite, dinoESprite, dinoCSprite, fundalSprite;
    sf::Sprite hpBarPlayerSprite, hpBarDinoSprite;
    sf::Sprite newGameButtonSprite, exitButtonSprite;
    sf::Sprite sprAtacSlab, sprAtacPuternic;
    sf::Sprite hitMissSprite;

    sf::RectangleShape backgroundBox;

    sf::Vector2f hitMissPosition;

    std::unique_ptr<Button> btnYes, btnNo;
    Dinozaur* currentDino = nullptr;

    sf::SoundBuffer hitSoundBuffer, missSoundBuffer;
    sf::Sound hitSound, missSound;

    std::vector<sf::RectangleShape> butoaneDialog;
    std::vector<sf::Text> texteOptiuni;

    void drawPlayerHP(sf::RenderWindow& window) const;
    void drawDialogElements(sf::RenderWindow& window);
    void drawTurnBanner(sf::RenderWindow& window, bool isPlayerTurn, const Dinozaur* currentDino, bool isTurnTransition, sf::Clock& turnDelayClock) const;
    void genereazaOptiuniDialog();
    void updateHPBar(sf::Sprite& sprite, int currentHP, int maxHP) const;
    bool afiseazaBannerDinozaur(const Dinozaur& dino, sf::RenderWindow& window) const;
    void showHitMissEffect(bool isHit, sf::Vector2f position, bool isPlayerAttacking);
    void handleEnemyTurn();
    void handlePlayerTurn(int attackType);
    void checkInactivity(float elapsedTime) override;

public:
    explicit GameScene(GameLogic& logic, sf::RenderWindow& window);
    //GameScene(const GameScene& other);

    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    //std::unique_ptr<Scene> clone() const override {
   //     return std::make_unique<GameScene>(*this);
  // }
};
