#pragma once
#include <string>
#include <iostream>

class Dinozaur {
    std::string nume;
    std::string tip;
    int agresivitate=0;
    int viata=0;

public:
    Dinozaur(std::string nume, std::string tip, int agresivitate, int viata);
    Dinozaur() = default;
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getTip() const;
    [[nodiscard]] int getAgresivitate() const;
    [[nodiscard]] int getViata() const;
    [[nodiscard]] bool checkHP() const;
    void takeDamage(int damage);
    [[nodiscard]] int getMaxHP() const;
    friend bool operator==(const Dinozaur& lhs, const Dinozaur& rhs);
    friend bool operator!=(const Dinozaur& lhs, const Dinozaur& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Dinozaur& d);
};