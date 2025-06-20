#include "../Header/Jucator.h"
#include <iostream>

Jucator::Jucator(const Jucator& other) : nume(other.nume), viata(other.viata) {
    std::cout << "Copiere Jucator: " << nume << "\n";
}

int Jucator::getViata() const { return viata; }
const std::string& Jucator::getName() const {
    return nume;
}
Jucator& Jucator::operator=(const Jucator& other) {
    if (this != &other) {
        nume = other.nume;
        viata = other.viata;
        dmg = other.dmg;
    }
    return *this;
}
bool Jucator::checkHP() const { return viata > 0; }
void Jucator::takeDamage(int damage) { viata -= damage; }
std::ostream& operator<<(std::ostream& os, const Jucator& j) {
    return os << "Jucator[" << j.nume << "|HP:" << j.viata << "]";
}
void Jucator::primViata(const int hp)
{
    viata+=hp;
}
int Jucator::Buff(int x)
{   dmg+=x;
    return dmg;
}
int Jucator::getMaxHP()
{
    return 100;
}
void Jucator::reset()
{
    viata=90;
}
