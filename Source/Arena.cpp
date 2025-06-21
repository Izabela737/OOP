#include "../Header/Arena.h"
#include <iostream>
#include <random>

bool Arena::inLupta = false;

bool Arena::atacRateaza(int sansa) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    return dist(gen) < sansa;
}

void Arena::atacSlab(Dinozaur& dino, Jucator& jucator)  {
        constexpr int x=0;
        dino.takeDamage(5 + jucator.Buff(x));
        std::cout << "Jucatorul a lovit dinozaurul!\n"<<jucator.Buff(x);
}

void Arena::atacPuternic(Dinozaur& dino )  {
        dino.takeDamage(25);
        std::cout << "Jucatorul a lovit dinozaurul!\n";

}

void Arena::startLupta(const Dinozaur& dino) {
    inLupta = true;
    std::cout << "Lupta începe între jucător și " << dino.getNume() << "!\n";
}

//bool Arena::eLuptaInDesfasurare() {
//    return inLupta;
//}

void Arena::reset() {
    inLupta = false;
}
bool Arena::procesTuraJucator(int tipAtac, Dinozaur& dino, Jucator& jucator) {
    bool aRatat = false;

    if (tipAtac == 1) {
        aRatat = atacRateaza(20);
        if (!aRatat) {
            atacSlab(dino, jucator);
        }
    }
    else if (tipAtac == 2) {
        aRatat = atacRateaza(60);
        if (!aRatat) {
            atacPuternic(dino);
        }
    }

    return aRatat;
}
