#include "../Header/GameLogic.h"
#include "../Header/Arena.h"
#include <iostream>
#include "../Header/MainMenuScene.h"
#include <random>
#include<algorithm>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Header/Dialog.h"
#include "../Header/DialogManager.h"


GameLogic::GameLogic(const std::string& numeJucator)
    : jucator(numeJucator)
{
    dialogManager.incarcaDinFisier("dialoguri.json");

}

void GameLogic::initializeGameData()
{
     dinozauri = {
         { "Gorath", "Carnivor", 10, 100 }, { "Varnok", "Carnivor", 8, 80 },
     { "Thalara", "Erbivor", 6, 60 }, { "Brundar", "Erbivor", 5, 50 },
     { "Skarnax", "Carnivor", 9, 90 }, { "Lunora", "Erbivor", 3, 30 },
     { "Drazhul", "Carnivor", 7, 70 }, { "Zephyra", "Carnivor", 6, 60 },
     { "Molgrim", "Erbivor", 4, 40 }, { "Xeroth", "Carnivor", 7, 70 },
     { "Elarin", "Erbivor", 5, 50 }, { "Kliktik", "Carnivor", 3, 30 },
     { "Sylphara", "Erbivor", 4, 40 }, { "Kaelor", "Carnivor", 8, 80 },
     { "Threxil", "Carnivor", 6, 60 }, { "Aurelyn", "Erbivor", 4, 40 },
     { "Zorthul", "Carnivor", 9, 90 }, { "Myrren", "Erbivor", 6, 60 },
     { "Cravik", "Carnivor", 5, 50 }, { "Fynora", "Erbivor", 3, 30 },
     { "Snarth", "Carnivor", 4, 40 }, { "Gribble", "Carnivor", 3, 30 }
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(dinozauri.begin(), dinozauri.end(), gen);
    dinozauri.resize(7);

}
void GameLogic::incarcaDialoguri(const std::string& fisier)
{
    std::ifstream f(fisier);
    if (!f) {
        std::cerr << "Eroare la deschiderea fisierului de dialog: " << fisier << "\n";
        return;
    }
    f >> dialoguri;
}

void GameLogic::handleEncounter(const Dinozaur& dino) {
    if (!jucator.checkHP()) {
        std::cout << "Jucatorul nu mai are viata!\n";

    }

    std::cout << "\nTe-ai intalnit cu: " << dino.getNume() << "\n";

    if (dino.getAgresivitate() >= 8) {
        Arena::startLupta(dino);
    } else if (dino.getAgresivitate() <= 5) {
        if (dino.getTip() == "Erbivor") {

            const ArboreDialog& dialog = dialogManager.alegeRandom("ErbivorP");
            sesiuneDialog = std::make_unique<DialogSession>(dialog);
        } else if (dino.getTip()  == "Carnivor") {
            const ArboreDialog& dialog = dialogManager.alegeRandom("CarnivorP");
            sesiuneDialog = std::make_unique<DialogSession>(dialog);
        }
    } else {
        if (dino.getTip()== "Erbivor")
        {
            const ArboreDialog& dialog = dialogManager.alegeRandom("Erbivor");
            sesiuneDialog = std::make_unique<DialogSession>(dialog);
        }
        else{
            const ArboreDialog& dialog = dialogManager.alegeRandom("Carnivor");
            sesiuneDialog = std::make_unique<DialogSession>(dialog);

    }
}
}

bool GameLogic::victoryCheck() const
{
    return indexDinoCurent >= dinozauri.size()+1 && jucator.checkHP();
}

void GameLogic::updateGame(float deltaTime) {
    (void)deltaTime;
}

bool GameLogic::checkGameOver() const
{
    return !jucator.checkHP();
}
Jucator& GameLogic::getJucator() {
    return jucator;
}

const std::vector<Dinozaur>& GameLogic::getDinozauri() const {
    return dinozauri;
}
Dinozaur& GameLogic::getDinoCurent() {
    return dinozauri[indexDinoCurent];
}
bool GameLogic::isLastDino() const {
    return indexDinoCurent == dinozauri.size()-1;
}
int GameLogic::indexCurent() const
{
    return static_cast<int>(indexDinoCurent);
}
void GameLogic::nextDino() {
    if (indexDinoCurent < dinozauri.size() - 1) {
        indexDinoCurent++;
        jucator.primViata(10);
        jucator.Buff(1);
    }
}

bool GameLogic::areDialogActiv() const {
    return sesiuneDialog != nullptr;
}

DialogSession* GameLogic::getDialog() const
{
    return sesiuneDialog.get();
}

void GameLogic::inchideDialog() {
    sesiuneDialog.reset();
}
void GameLogic::resetGame()
{
    dinozauri.clear();
    initializeGameData();
    indexDinoCurent = 0;
    jucator.reset();
    sesiuneDialog.reset();
}


