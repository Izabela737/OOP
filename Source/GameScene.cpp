#include <SFML/Graphics.hpp>
#include "../Header/GameLogic.h"
#include "../Header/GameScene.h"
#include <iostream>
#include <random>
#include <chrono>
#include "../Header/Button.h"
#include "../Header/Arena.h"

GameScene::GameScene(GameLogic& logic,sf::RenderWindow& window)
    : gameLogic(logic) ,window(window)
{
    turnText.setFont(font);
    turnText.setCharacterSize(36);
    turnText.setFillColor(sf::Color::Yellow);
    turnText.setStyle(sf::Text::Bold);
    turnText.setPosition(static_cast <float>(window.getSize().x)/2 - 100, 20);
    sf::FloatRect boundsTurn = turnText.getLocalBounds();
    turnText.setOrigin(boundsTurn.width/2, boundsTurn.height/2);
    turnText.setPosition(static_cast<float>( window.getSize().x)/2, 40);
    hitSoundBuffer.loadFromFile("sound/hit.mp3");
    missSoundBuffer.loadFromFile("sound/miss.mp3");
    hitSound.setBuffer(hitSoundBuffer);
    missSound.setBuffer(missSoundBuffer);
    hitSound.setVolume(50.f);
    if (!hitTexture.loadFromFile("imagini/hit.png")) {
        throw std::runtime_error("Nu am găsit hit.png!");
    }
    if (!missTexture.loadFromFile("imagini/miss.png")) {
        throw std::runtime_error("Nu am găsit miss.png!");
    }
    HP.loadFromFile("imagini/hp.png");
    hitMissSprite.setScale(0.04f, 0.04f);
    hpBar0.loadFromFile("imagini/hp_0.png");
    hpBar25.loadFromFile("imagini/hp_25.png");
    hpBar50.loadFromFile("imagini/hp_50.png");
    hpBar75.loadFromFile("imagini/hp_75.png");
    hpBar100.loadFromFile("imagini/hp_100.png");
    hpBarDinoSprite.setScale(0.4f, 0.4f);
    hpBarPlayerSprite.setScale(0.4f, 0.4f);
    hpBarPlayerSprite.setPosition(50, 50);
    hpBarDinoSprite.setPosition(static_cast<float>(window.getSize().x) - 250, 50);
    if (!playerTexture.loadFromFile("imagini/player.png")) {
        throw std::runtime_error("nu am gasit imaginea player.png");
    }
    playerSprite.setTexture(playerTexture);

    float scaleDino = 250.f / static_cast <float>(playerTexture.getSize().x);
    playerSprite.setScale(scaleDino, scaleDino);
    sf::FloatRect boundsP = playerSprite.getLocalBounds();
    playerSprite.setOrigin(boundsP.width / 2.f, boundsP.height);
    playerSprite.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - 200.f,
        static_cast<float>(window.getSize().y) - 50.f
    );

    dinoCTexture.loadFromFile( "imagini/dinoC1.png");
    dinoCSprite.setTexture(dinoCTexture);
    float scaleDinoC = 350.f / static_cast <float>(dinoCTexture.getSize().x);
    dinoCSprite.setScale(scaleDinoC, scaleDinoC);
    sf::FloatRect boundsC = dinoCSprite.getLocalBounds();
    dinoCSprite.setOrigin(boundsC.width / 2.f, boundsC.height);
    dinoCSprite.setPosition(
        static_cast<float>(window.getSize().x) / 2.f + 200.f,
        static_cast<float>(window.getSize().y) - 50.f
    );
    dinoETexture.loadFromFile( "imagini/dinoE1.png");
    dinoESprite.setTexture(dinoETexture);
    sf::FloatRect boundsE = dinoESprite.getLocalBounds();
    dinoESprite.setOrigin(boundsE.width / 2.f, boundsE.height);
    dinoESprite.setPosition(
    static_cast<float>(window.getSize().x) / 2.f + 200.f,
    static_cast<float>(window.getSize().y) - 50.f
    );

    state = GameState::Intro;
    isPlayerTurn = true;
    isTurnTransition = false;

    if (!font.loadFromFile("fonts/geo.ttf")) {
        std::cerr << "Eroare la încărcarea fontului!\n";
    }

    mesajDialog.setFont(font);
    mesajDialog.setCharacterSize(24);
    mesajDialog.setFillColor(sf::Color::White);
    mesajDialog.setPosition(100, static_cast<float>(window.getSize().y) - 150);
    sf::FloatRect textBounds = mesajDialog.getGlobalBounds();

    backgroundBox.setFillColor(sf::Color(0, 0, 0, 180));
    backgroundBox.setOutlineColor(sf::Color::White);
    backgroundBox.setOutlineThickness(2.f);
    backgroundBox.setSize(sf::Vector2f(textBounds.width + 20.f, textBounds.height + 20.f));
    backgroundBox.setPosition(textBounds.left - 10.f, textBounds.top - 10.f);

    if (!fundalTexture.loadFromFile("imagini/fundall.png"))
    {
        throw std::runtime_error("Failed to load background  image");
    }
    fundalSprite.setTexture(fundalTexture);
    sf::FloatRect bgBounds = fundalSprite.getLocalBounds();
    fundalSprite.setOrigin(bgBounds.width / 2.f, bgBounds.height / 2.f);
    fundalSprite.setPosition(static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f);

    line1.setFont(font);
    line2.setFont(font);
    line3.setFont(font);
    line4.setFont(font);

    line1.setString("In Ceratopolis every dinosaur who wants to become a fighter");
    line2.setString("has to complete his training.");
    line3.setString("This dinosaur just completed his and now it's time to go back home.");
    line4.setString("The journey is known to be long and dangerous but he believes he can do it!");

    line1.setFillColor(sf::Color::Black);
    line2.setFillColor(sf::Color::Black);
    line3.setFillColor(sf::Color::Black);
    line4.setFillColor(sf::Color::Black);

    line1.setCharacterSize(20);
    line2.setCharacterSize(20);
    line3.setCharacterSize(20);
    line4.setCharacterSize(18);

    line1.setOrigin(line1.getLocalBounds().width / 2, 0);
    line2.setOrigin(line2.getLocalBounds().width / 2, 0);
    line3.setOrigin(line3.getLocalBounds().width / 2, 0);
    line4.setOrigin(line4.getLocalBounds().width / 2, 0);

    float startY = static_cast<float>(window.getSize().x) / 2 - 200;
    float lineSpacing = 50.f;

    line1.setPosition(static_cast<float>(window.getSize().x) / 2, startY);
    line2.setPosition(static_cast<float>(window.getSize().x) / 2, startY + lineSpacing);
    line3.setPosition(static_cast<float>(window.getSize().x) / 2, startY + 2 * lineSpacing);
    line4.setPosition(static_cast<float>(window.getSize().x) / 2, startY + 3 * lineSpacing);

    if (!backgroundTexture.loadFromFile("imagini/encscene.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    backgroundSprite.setTexture(backgroundTexture);

    const sf::Vector2u textureSize = backgroundTexture.getSize();
    const sf::Vector2u windowSize = window.getSize();
    const float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    const float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);
    backgroundSprite.setScale(scaleX, scaleY);

    if (!waitTexture.loadFromFile("imagini/wait.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    waitSprite.setTexture(waitTexture);
    const sf::Vector2u WtextureSize = waitTexture.getSize();

    const float scaleXW = static_cast<float>(windowSize.x) / static_cast<float>(WtextureSize.x);
    const float scaleYW = static_cast<float>(windowSize.y) / static_cast<float>(WtextureSize.y);
    waitSprite.setScale(scaleXW, scaleYW);
    if (!endTexture.loadFromFile("imagini/gameover.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    endSprite.setTexture(endTexture);
    const sf::Vector2u EtextureSize = endTexture.getSize();
    const float scaleXE = static_cast<float>(windowSize.x) / static_cast<float>(EtextureSize.x);
    const float scaleYE = static_cast<float>(windowSize.y) / static_cast<float>(EtextureSize.y);
    endSprite.setScale(scaleXE, scaleYE);
    if (!vicTexture.loadFromFile("imagini/vic.png")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    vicSprite.setTexture(vicTexture);
    vicSprite.setScale(1.5f, 1.5f);
    sf::FloatRect boundsVic = vicSprite.getGlobalBounds(); 
    float centerX = (static_cast<float>(windowSize.x) - boundsVic.width) / 2.f;
    float centerY = (static_cast<float>(windowSize.y) - boundsVic.height) / 2.f;
    vicSprite.setPosition(centerX, centerY);

    if (!vicBackgroundTexture.loadFromFile("imagini/screen.jpg")) {
        throw std::runtime_error("Failed to load background menu image");
    }
    vicBackgroundSprite.setTexture(vicBackgroundTexture);
    const sf::Vector2u textureVic = vicBackgroundTexture.getSize();
    const float scalevicX = static_cast<float>(windowSize.x) / static_cast<float>(textureVic.x);
    const float scalevicY = static_cast<float>(windowSize.y) / static_cast<float>(textureVic.y);
    vicBackgroundSprite.setScale(scalevicX, scalevicY);

    waitingText.setFont(font);
    waitingText.setCharacterSize(28);
    waitingText.setFillColor(sf::Color::White);
    waitingText.setString("Click to continue...");
    sf::FloatRect bounds1 = waitingText.getLocalBounds();
    waitingText.setOrigin(bounds1.width / 2.f, bounds1.height / 2.f);
    waitingText.setPosition(static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 1.5f+100.f);

    if (!texAtacSlab.loadFromFile("imagini/AtkS.png"))
        throw std::runtime_error("nu am gasit imaginea atac_slab.png");
    sprAtacSlab.setTexture(texAtacSlab);
    sprAtacSlab.setPosition(0.f, 510.f);
    const float scale1 = 100.f / static_cast<float>( texAtacSlab.getSize().x);
    sprAtacSlab.setScale(scale1, scale1);

    if (!texAtacPuternic.loadFromFile("imagini/AtkP.png"))
        throw std::runtime_error("nu am gasit imaginea atac_puternic.png");
    sprAtacPuternic.setTexture(texAtacPuternic);
    sprAtacPuternic.setPosition(80.f, 510.f);
    float scale2 = 100.f / static_cast<float>(texAtacPuternic.getSize().x);
    sprAtacPuternic.setScale(scale2, scale2);

    if (!newGameButtonTexture.loadFromFile("imagini/Bstart.png")) {
        throw std::runtime_error("Nu s-a putut încărca newGame.png");
    }
    if (!exitButtonTexture.loadFromFile("imagini/Bexit.png")) {
        throw std::runtime_error("Nu s-a putut încărca Bexit.png");
    }

    newGameButtonSprite.setTexture(newGameButtonTexture);
    exitButtonSprite.setTexture(exitButtonTexture);

    newGameButtonSprite.setScale(0.8f, 0.8f);
    exitButtonSprite.setScale(0.8f, 0.8f);

    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    constexpr float margin = 50.f;

    constexpr float newGameX = margin;
    const float newGameY = windowHeight - margin - newGameButtonSprite.getGlobalBounds().height;
    newGameButtonSprite.setPosition(newGameX, newGameY);

    const float exitX = windowWidth - margin - exitButtonSprite.getGlobalBounds().width;
    const float exitY = windowHeight - margin - exitButtonSprite.getGlobalBounds().height;
    exitButtonSprite.setPosition(exitX, exitY);
}

void GameScene::update(float deltaTime, sf::RenderWindow& win) {
    (void)win;
    timeInScene += deltaTime;
    if (state == GameState::Playing || state == GameState::Fighting) {
        inactivityTime += deltaTime;
        checkInactivity(deltaTime);
    } else {
        inactivityTime = 0.f;
    }
    if (isTurnTransition) {
        if (turnDelayClock.getElapsedTime().asSeconds() >= 1.0f) {
            isTurnTransition = false;
            isPlayerTurn = !isPlayerTurn;
        }
        return;
    }
    if (showHitMiss) {
        hitMissTimer += deltaTime;
        if (hitMissTimer >= 0.5f) {
            showHitMiss = false;
        } else {
            hitMissScale = 0.1f + (hitMissTimer / 0.5f) * 0.9f;
            hitMissSprite.setScale(hitMissScale, hitMissScale);
        }
    }
    if (state == GameState::IntroEncounter) {
        if (introClock.getElapsedTime().asSeconds() >= introDuration) {
            if (currentDino && currentDino->getAgresivitate() >= 8) {
                state = GameState::Fighting;
                isPlayerTurn = true;
                isTurnTransition = false;
            } else {
                state = GameState::Playing;
                encounterStarted = false;
            }
        }
    }
    else if (state == GameState::Fighting) {
        if (!isPlayerTurn) {
            handleEnemyTurn();
        }
    }
    else if (state == GameState::Playing) {
        if (!encounterStarted) {
            currentDino = &gameLogic.getDinoCurent();
            gameLogic.handleEncounter(*currentDino);
            genereazaOptiuniDialog();
            encounterStarted = true;
        }
        else if (!gameLogic.areDialogActiv()) {
            state = GameState::Waiting;
            waitingClock.restart();
            canClick = false;
            encounterStarted = false;
        }
    }
    else if (state == GameState::Waiting) {
        if (!canClick && waitingClock.getElapsedTime().asSeconds() >= 1.5f) {
            canClick = true;
        }
    }
}
void GameScene::handleEvent(sf::Event& event, sf::RenderWindow& win)
{
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
        inactivityTime = 0.f;
        inactivityMessageShown = false;

    }

    if (state == GameState::Intro) {

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            state = GameState::Waiting;
            waitingClock.restart();
            canClick = false;
        }
    }

    if (state == GameState::Playing|| state == GameState::Waiting|| state==GameState::IntroEncounter|| state==GameState::Fighting)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            isPaused = !isPaused;

            if (!isPaused) {
                btnYes.reset();
                btnNo.reset();
                btnYesCreated = false;
            }
        }

        if (isPaused) {
            if (!btnYesCreated) {
                btnYes = std::make_unique<Button>("Da", font, sf::Vector2f(250, 300), sf::Vector2f(100, 50));
                btnNo = std::make_unique<Button>("Nu", font, sf::Vector2f(450, 300), sf::Vector2f(100, 50));
                btnYesCreated = true;
            }

            if (btnYes && btnNo) {
                btnYes->update(win);
                btnNo->update(win);

                if (btnYes->isClicked(win)) {
                    win.close();
                }

                if (btnNo->isClicked(win)) {
                    isPaused = false;
                    btnYes.reset();
                    btnNo.reset();
                    btnYesCreated = false;
                }
            }
        }else
        {
            if (state == GameState::Waiting) {
                if (canClick &&
                    event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    if (!dataInitialized) {
                        gameLogic.initializeGameData();
                        currentDino = &gameLogic.getDinoCurent();
                        introClock.restart();
                        state = GameState::IntroEncounter;
                        dataInitialized = true;
                    }
                    else if (!gameLogic.checkGameOver()) {
                        if (!gameLogic.isLastDino())
                        {
                            gameLogic.nextDino();
                            updateHPBar(hpBarDinoSprite, currentDino->getViata(), currentDino->getMaxHP());
                            state = GameState::IntroEncounter;
                            introClock.restart();
                            currentDino = &gameLogic.getDinoCurent();
                        }
                        else
                        {   isTurnTransition=true;
                            state=GameState::Victory;
                        }
                    }
                }
            }if (state == GameState::Fighting && isPlayerTurn && !isTurnTransition) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    auto mousePos = win.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    int attackType = 0;
                    if (sprAtacSlab.getGlobalBounds().contains(mousePos)) {
                        attackType = 1;
                    }
                    else if (sprAtacPuternic.getGlobalBounds().contains(mousePos)) {
                        attackType = 2;
                    }
                    if (attackType != 0) {
                        handlePlayerTurn(attackType);
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));

                if (gameLogic.areDialogActiv()) {
                    DialogSession* sesiune = gameLogic.getDialog();
                    const auto& optiuni = sesiune->getOptiuni();

                    for (size_t i = 0; i < butoaneDialog.size(); ++i) {
                        if (butoaneDialog[i].getGlobalBounds().contains(mousePos)) {
                            if (i >= optiuni.size()) continue;
                            std::string next = optiuni[i].next;

                            if (next == "end") {
                                gameLogic.inchideDialog();
                                return;
                            }
                            if (next == "fight") {
                                butoaneDialog.clear();
                                texteOptiuni.clear();
                                gameLogic.inchideDialog();
                                state = GameState::Fighting;
                                updateHPBar(hpBarPlayerSprite, gameLogic.getJucator().getViata(), Jucator::getMaxHP());
                                updateHPBar(hpBarDinoSprite, currentDino->getViata(), currentDino->getMaxHP());
                                return;
                            }
                            if (next.starts_with("viata+")) {
                                const int val = std::stoi(next.substr(6));
                                gameLogic.getJucator().primViata(val);
                                updateHPBar(hpBarPlayerSprite, gameLogic.getJucator().getViata(),Jucator::getMaxHP());
                                gameLogic.inchideDialog();
                                return;
                            }
                            if (next.starts_with("viata-")) {
                                const int val = std::stoi(next.substr(6));
                                gameLogic.getJucator().takeDamage(val);
                                if (!gameLogic.getJucator().checkHP())
                                {
                                    isTurnTransition = true;
                                    state = GameState::GameOver;
                                }
                                else {updateHPBar(hpBarPlayerSprite, gameLogic.getJucator().getViata(),Jucator::getMaxHP());}
                                gameLogic.inchideDialog();
                                return;
                            }
                            if (next.starts_with("buff+")) {
                                const int val = std::stoi(next.substr(5));
                                gameLogic.getJucator().Buff(val);
                                gameLogic.inchideDialog();
                                return;
                            }

                            sesiune->selecteazaOptiune(static_cast<int>(i));

                            if (!sesiune->isIncheiat()) {
                                genereazaOptiuniDialog();
                            } else {
                                gameLogic.inchideDialog();
                                butoaneDialog.clear();
                                texteOptiuni.clear();
                            }

                            break;
                        }
                    }
                }
            }
        }
    }
    else if (state==GameState::GameOver||state==GameState::Victory)
    {
        sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (newGameButtonSprite.getGlobalBounds().contains(mousePos)) {
                gameLogic.resetGame();
                state=GameState::Waiting;
            }else if (exitButtonSprite.getGlobalBounds().contains(mousePos)) {  win.close(); }
        }
    }
}

void GameScene::draw(sf::RenderWindow& win) {
    if (state == GameState::Intro) {
        win.clear(sf::Color::Black);
        win.draw(fundalSprite);
        win.draw(line1);
        win.draw(line2);
        win.draw(line3);
        win.draw(line4);
        win.draw(line5);
        win.draw(waitingText);
    }
    else if (state == GameState::IntroEncounter) {
        win.clear();
        win.draw(backgroundSprite);
        win.draw(playerSprite);
        if (currentDino != nullptr) {
            if (currentDino->getTip()=="Carnivor")
            {
                win.draw(dinoCSprite);
            }else
            {
                win.draw(dinoESprite);
            }
            if (currentDino->getAgresivitate() >= 8) {
                updateHPBar(hpBarPlayerSprite, gameLogic.getJucator().getViata(), Jucator::getMaxHP());
                updateHPBar(hpBarDinoSprite, currentDino->getViata(), currentDino->getMaxHP());
                win.draw(hpBarPlayerSprite);
                win.draw(hpBarDinoSprite);
            }
            else  drawPlayerHP(win);
            afiseazaBannerDinozaur(*currentDino, win);
        }
    }
    else if (state == GameState::Playing)
    {
        win.clear();
        win.draw(backgroundSprite);
        win.draw(playerSprite);
        if (currentDino != nullptr)
        {
            if (currentDino->getTip()=="Carnivor")
            {
                win.draw(dinoCSprite);
            }else
            {
                win.draw(dinoESprite);
            }
        }
        drawPlayerHP(win);

    }else if (state==GameState::Fighting)
    {
        win.clear();
        win.draw(backgroundSprite);
        win.draw(playerSprite);
        if (currentDino != nullptr)
        {   updateHPBar(hpBarDinoSprite, currentDino->getViata(), currentDino->getMaxHP());
            if (currentDino->getTip()=="Carnivor")
            {
                win.draw(dinoCSprite);
            }else
            {
                win.draw(dinoESprite);
            }
        }
        win.draw(hpBarPlayerSprite);
        win.draw(hpBarDinoSprite);
        drawTurnBanner(win, isPlayerTurn, currentDino, isTurnTransition, turnDelayClock);
        if (showHitMiss) {
            hitMissSprite.setPosition(hitMissPosition);
            win.draw(hitMissSprite);
        }
        win.draw(sprAtacSlab);
        win.draw(sprAtacPuternic);
    }
    if (state == GameState::Waiting) {
        win.clear();
        win.draw(waitSprite);
        if (canClick) {
            win.draw(waitingText);
        }
    }
    if (state == GameState::GameOver)
    {
        win.clear();
        win.draw(endSprite);
        win.draw(newGameButtonSprite);
        win.draw(exitButtonSprite);
    }
    if (state == GameState::Victory)
    {
        win.clear();
        win.draw(vicBackgroundSprite);
        win.draw(vicSprite);
        win.draw(newGameButtonSprite);
        win.draw(exitButtonSprite);
    }
    if (gameLogic.areDialogActiv()) {
       drawDialogElements(win);
    }
    if (isPaused) {
        sf::RectangleShape overlay({800.f, 600.f});
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        win.draw(overlay);

        sf::RectangleShape pauseWindow({400, 200});
        pauseWindow.setPosition(200, 200);
        pauseWindow.setFillColor(sf::Color(70, 70, 70));
        win.draw(pauseWindow);

        sf::Text pauseText("Sigur vrei sa iesi?", font, 30);
        pauseText.setPosition(220, 220);
        win.draw(pauseText);

        if (btnYes && btnNo) {
            btnYes->draw(win);
            btnNo->draw(win);
        }
    }
}
bool GameScene::afiseazaBannerDinozaur(const Dinozaur& dino, sf::RenderWindow& win) const
{
    constexpr float bannerHeight = 120.f;
    constexpr float padding = 20.f;

    sf::RectangleShape banner(sf::Vector2f(static_cast<float>(win.getSize().x), bannerHeight));
    banner.setFillColor(sf::Color(30, 30, 40, 220));
    banner.setOutlineColor(sf::Color(200, 180, 100));
    banner.setOutlineThickness(2.f);
    banner.setPosition(0.f, 50.f);
    win.draw(banner);

    sf::Text titlu;
    titlu.setFont(font);
    titlu.setCharacterSize(24);
    titlu.setFillColor(sf::Color(255, 215, 0));

    int index = gameLogic.indexCurent();
    std::string sufix = (index == 0) ? "1st" : (index == 1) ? "2nd" : (index==2) ? "3rd" : std::to_string(index + 1) + "th";
    titlu.setString(sufix + " Dinosaur");

    sf::FloatRect titluBounds = titlu.getLocalBounds();
    titlu.setPosition(
        static_cast<float>(win.getSize().x) / 2.f - titluBounds.width / 2.f,
        banner.getPosition().y + 5.f
    );
    win.draw(titlu);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::White);
    text.setString(
        "Name: " + dino.getNume() +
        "\nHealth: " + std::to_string(dino.getViata()) +
        "\nAggressiveness: " + std::to_string(dino.getAgresivitate())
    );
    text.setPosition(
        padding,
        titlu.getPosition().y + titluBounds.height + 5.f
    );

    win.draw(text);
    return dino.getAgresivitate() >= 8;
}
void GameScene::drawTurnBanner(sf::RenderWindow& win, bool isPlayerTurn1, const Dinozaur* currentDino1, bool isTurnTransition1, sf::Clock& turnDelayClock1) const
{
    std::string turnStr;
    if (isPlayerTurn1) {
        turnStr = gameLogic.getJucator().getName() + "'s Turn";
    } else if (currentDino1) {
        turnStr = currentDino1->getNume() + "'s Turn";
    } else {
        return;
    }

    sf::Text turnText1;
    turnText1.setFont(font);
    turnText1.setCharacterSize(24);
    turnText1.setString(turnStr);
    turnText1.setFillColor(sf::Color(200, 180, 100));

    sf::Uint8 alpha = 255;
    if (isTurnTransition1) {
        float progress = turnDelayClock1.getElapsedTime().asSeconds() / 1.0f;
        progress = std::min(progress, 1.0f);
        alpha = static_cast<sf::Uint8>(255 * (1.0f - progress));
    }
    turnText1.setFillColor(sf::Color(
        turnText1.getFillColor().r,
        turnText1.getFillColor().g,
        turnText1.getFillColor().b,
        alpha
    ));

    sf::FloatRect textBounds = turnText1.getLocalBounds();
    sf::Vector2f containerSize(textBounds.width + 40.f, textBounds.height + 30.f);
    sf::RectangleShape container(containerSize);
    container.setFillColor(sf::Color(30, 30, 40, alpha));
    container.setOutlineColor(sf::Color(200, 180, 100, alpha));
    container.setOutlineThickness(2.f);
    container.setPosition(
        static_cast<float>(win.getSize().x) / 2.f - containerSize.x / 2.f,
        20.f
    );
    turnText1.setPosition(
        container.getPosition().x + (containerSize.x - textBounds.width) / 2.f - textBounds.left,
        container.getPosition().y + (containerSize.y - textBounds.height) / 2.f - textBounds.top
    );

    win.draw(container);
    win.draw(turnText1);
}
void GameScene::genereazaOptiuniDialog() {
    butoaneDialog.clear();
    texteOptiuni.clear();

    DialogSession* sesiune = gameLogic.getDialog();
    if (!sesiune) return;

    constexpr float dialogHeight = 150.f;
    const auto& optiuni = sesiune->getOptiuni();
    const float startY = static_cast<float>(window.getSize().y) - dialogHeight - 20.f - (static_cast<float>(optiuni.size()) * 70.f);

    for (size_t i = 0; i < optiuni.size(); ++i) {
        constexpr float buttonLeftMargin = 30.f;

        sf::Text tempText(optiuni[i].text, font, 20);
        sf::FloatRect bounds = tempText.getLocalBounds();
        sf::Vector2f buttonSize(bounds.width + 30.f, bounds.height + 20.f);
        sf::RectangleShape buton(buttonSize);
        buton.setFillColor(sf::Color(50, 50, 70, 200));
        buton.setOutlineColor(sf::Color(200, 180, 100));
        buton.setOutlineThickness(1.f);
        buton.setPosition(buttonLeftMargin, startY + static_cast<float>(i) * 70.f);

        sf::Text text;
        text.setFont(font);
        text.setString(optiuni[i].text);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(
            buton.getPosition().x + 15.f,
            buton.getPosition().y + 10.f
        );
        butoaneDialog.push_back(buton);
        texteOptiuni.push_back(text);
    }
}
void GameScene::drawDialogElements(sf::RenderWindow& win) {

    if (const DialogSession* sesiune = gameLogic.getDialog()) {
        mesajDialog.setString(sesiune->getMesaj());
    }else return;

    constexpr float dialogHeight = 100.f;
    constexpr float padding = 20.f;

    sf::RectangleShape dialogBackground;
    dialogBackground.setSize(sf::Vector2f(static_cast<float>(win.getSize().x), dialogHeight));
    dialogBackground.setPosition(0.f, static_cast<float>(win.getSize().y) - dialogHeight);
    dialogBackground.setFillColor(sf::Color(30, 30, 40, 220));
    win.draw(dialogBackground);

    sf::Text numeDinozaur;
    numeDinozaur.setFont(font);
    numeDinozaur.setString(gameLogic.getDinoCurent().getNume());
    numeDinozaur.setCharacterSize(24);
    numeDinozaur.setFillColor(sf::Color(255, 215, 0));
    sf::FloatRect numeBounds = numeDinozaur.getLocalBounds();
    numeDinozaur.setPosition(
        static_cast<float>(win.getSize().x) / 2.f - numeBounds.width / 2.f,
        static_cast<float>(win.getSize().y) - dialogHeight + padding
    );
    win.draw(numeDinozaur);

    mesajDialog.setFont(font);
    mesajDialog.setCharacterSize(20);
    mesajDialog.setFillColor(sf::Color::White);
    sf::FloatRect msgBounds = mesajDialog.getLocalBounds();
    mesajDialog.setPosition(
        static_cast<float>(win.getSize().x) / 2.f - msgBounds.width / 2.f,
        numeDinozaur.getPosition().y + numeDinozaur.getLocalBounds().height + 10.f
    );

    sf::Text shadowText = mesajDialog;
    shadowText.setFillColor(sf::Color(0, 0, 0, 150));
    shadowText.move(2, 2);
    win.draw(shadowText);
    win.draw(mesajDialog);

    for (size_t i = 0; i < butoaneDialog.size(); ++i) {

        if (butoaneDialog[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win)))) {
            butoaneDialog[i].setFillColor(sf::Color(70, 70, 90, 200));
        } else {
            butoaneDialog[i].setFillColor(sf::Color(50, 50, 70, 200));
        }
        win.draw(butoaneDialog[i]);
        win.draw(texteOptiuni[i]);
    }
}
void GameScene::drawPlayerHP(sf::RenderWindow& win) const
{
    const auto& player = gameLogic.getJucator();
    int hp = player.getViata();

    sf::Sprite hpIcon;
    hpIcon.setTexture(HP);
    hpIcon.setScale(0.5f, 0.5f);
    hpIcon.setPosition(20.f, 20.f);

    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::White);
    hpText.setString(std::to_string(hp));
    hpText.setPosition(hpIcon.getPosition().x + hpIcon.getGlobalBounds().width + 10.f, hpIcon.getPosition().y + 5.f);

    sf::RectangleShape background;
    background.setSize(sf::Vector2f( hpText.getPosition().x + hpText.getLocalBounds().width + 20.f, hpIcon.getGlobalBounds().height  + 20.f));
    background.setPosition(10.f, 15.f);
    background.setFillColor(sf::Color(30, 30, 40, 200));
    background.setOutlineColor(sf::Color(200, 180, 100));
    background.setOutlineThickness(1.f);

    win.draw(background);
    win.draw(hpIcon);
    win.draw(hpText);
}
void GameScene::updateHPBar(sf::Sprite& sprite, int currentHP, int maxHP) const
{
    float procent = (static_cast<float>(currentHP) /static_cast<float>( maxHP)) * 100;

    if (procent >= 75) {
        sprite.setTexture(hpBar100);
    } else if (procent >= 50) {
        sprite.setTexture(hpBar75);
    } else if (procent >= 25) {
        sprite.setTexture(hpBar50);
    } else if (procent > 0) {
        sprite.setTexture(hpBar25);
    } else {
        sprite.setTexture(hpBar0);
    }
}
void GameScene::showHitMissEffect(bool isHit, sf::Vector2f position, bool isPlayerAttacking) {
    showHitMiss = true;
    hitMissTimer = 0.5f;
    hitMissPosition = position;

    if (isHit) {
        hitMissSprite.setTexture(hitTexture);
        hitMissSprite.setColor(isPlayerAttacking ? sf::Color::Green : sf::Color::Red);
        hitSound.play();
    } else {
        hitMissSprite.setTexture(missTexture);
        hitMissSprite.setColor(sf::Color::White);
        missSound.play();
    }
    hitMissSprite.setScale(0.07f, 0.07f);
    sf::FloatRect bounds = hitMissSprite.getLocalBounds();
    hitMissSprite.setOrigin(bounds.width/2, bounds.height/2);

}
void GameScene::handleEnemyTurn() {
    const Dinozaur& dino = gameLogic.getDinoCurent();
    Jucator& jucator = gameLogic.getJucator();
    bool missed = Arena::atacRateaza(25);

    isTurnTransition = true;
    turnDelayClock.restart();

    showHitMissEffect(!missed, playerSprite.getPosition() + sf::Vector2f(0, -100), false);

    if (!missed) {
        int damage = static_cast<int>(std::round(1.5 * dino.getAgresivitate()));
        jucator.takeDamage(damage);
        updateHPBar(hpBarPlayerSprite, jucator.getViata(), Jucator::getMaxHP());
    }

    if (!jucator.checkHP()) {
        isTurnTransition=true;
        state = GameState::GameOver;
    }
}
void GameScene::handlePlayerTurn(int attackType) {
    bool aRatat = Arena::procesTuraJucator(attackType, *currentDino, gameLogic.getJucator());

    isTurnTransition = true;
    turnDelayClock.restart();

    sf::Vector2f dinoPos = (currentDino->getTip() == "Carnivor")
        ? dinoCSprite.getPosition() + sf::Vector2f(0, -100)
        : dinoESprite.getPosition() + sf::Vector2f(0, -100);
    showHitMissEffect(!aRatat, dinoPos, true);

    updateHPBar(hpBarDinoSprite, currentDino->getViata(), currentDino->getMaxHP());

    if (!currentDino->checkHP()) {
        state = GameState::Waiting;
        waitingClock.restart();
        canClick = false;
    }
}
void GameScene::checkInactivity(float elapsedTime) {
    inactivityTime += elapsedTime;

    if (state == GameState::Playing) {
        if (inactivityTime > 7.f && !inactivityMessageShown) {
            std::cout << "Hai odata mai repede!\n";
            inactivityMessageShown = true;
        }
    } else if (state == GameState::Fighting) {
        if (inactivityTime > 5.f && !inactivityMessageShown) {
            std::cout << "Nu sta pe loc, atacă!\n";
            inactivityMessageShown = true;
        }
    } else {
        inactivityTime = 0.f;
        inactivityMessageShown = false;
    }
}

