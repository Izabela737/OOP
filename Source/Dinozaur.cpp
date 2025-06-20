#include "../Header/Dinozaur.h"

Dinozaur::Dinozaur(std::string nume, std::string tip, int agresivitate, int viata)
    : nume(std::move(nume)), tip(std::move(tip)), agresivitate(agresivitate), viata(viata) {}

const std::string& Dinozaur::getNume() const { return nume; }
const std::string& Dinozaur::getTip() const { return tip; }
int Dinozaur::getAgresivitate() const { return agresivitate; }
int Dinozaur::getViata() const { return viata; }

bool Dinozaur::checkHP() const { return viata > 0; }
void Dinozaur::takeDamage(int damage) { viata -= damage; }

bool operator==(const Dinozaur& lhs, const Dinozaur& rhs) {
    return lhs.nume == rhs.nume
        && lhs.tip == rhs.tip
        && lhs.agresivitate == rhs.agresivitate
        && lhs.viata == rhs.viata;
}
bool operator!=(const Dinozaur& lhs, const Dinozaur& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Dinozaur& d) {
    return os << "Dinozaur " << d.nume << " | Tip: " << d.tip << " | HP: "
             << d.viata << " | Agresivitate: " << d.agresivitate << std::endl;
}
int Dinozaur::getMaxHP() const {
    return 30 + (agresivitate - 3) * 10;
}