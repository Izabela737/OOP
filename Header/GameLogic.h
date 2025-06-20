#pragma once
#include "Dinozaur.h"
#include "Jucator.h"
#include "MainMenuScene.h"
#include <nlohmann/json.hpp>
#include "DialogManager.h"
#include "DialogSession.h"

class GameLogic {
    std::vector<Dinozaur> dinozauri;
    Jucator jucator;
    std::string numeJucator;
    size_t indexDinoCurent = 0;
    nlohmann::json dialoguri;
    std::unique_ptr<DialogSession> sesiuneDialog;
    DialogManager dialogManager;

public:
    explicit GameLogic(const std::string& numeJucator);
    static void updateGame(float deltaTime);
    [[nodiscard]] bool checkGameOver() const;
    Jucator& getJucator();
    [[nodiscard]] const std::vector<Dinozaur>& getDinozauri() const;
    void initializeGameData();
    void handleEncounter(const Dinozaur& dino);
    Dinozaur& getDinoCurent();
    [[nodiscard]] bool isLastDino() const;
    void nextDino();
    [[nodiscard]] bool victoryCheck() const;
    void incarcaDialoguri(const std::string& fisier);
    bool areDialogActiv() const;
    DialogSession* getDialog() const;
    void inchideDialog();
    void resetGame();
    int indexCurent() const;
};