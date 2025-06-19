#pragma once
#include <string>
#include <iostream>
#include <utility>

class Jucator {
    std::string nume;
    int viata;
    int dmg=0;

public:
    explicit Jucator(std::string  nume) : nume(std::move(nume)), viata(100) {}
    Jucator(const Jucator& other);
    std::string getName();
    [[nodiscard]] int getViata() const;
    Jucator& operator=(const Jucator& other);
    [[nodiscard]] bool checkHP() const;
    void takeDamage(int damage);
    void primViata(int hp);
    int Buff(int x);
    void reset();
    [[nodiscard]] static int getMaxHP();
    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);
};