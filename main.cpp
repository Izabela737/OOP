#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

class Jucator
{
    std::string nume;
    int viata;

public:
    explicit Jucator(std::string  nume) : nume(std::move(nume)), viata(50){}

    // Constructor de copiere
    Jucator(const Jucator& other)
        : nume(other.nume), viata(other.viata) {
        std::cout << "Copiere Jucator: " << nume << "\n";
    }
    [[nodiscard]] int getViata() const { return viata; }

    Jucator& operator=(const Jucator& other) {
        if (this != &other) {
            nume = other.nume;
            viata = other.viata;
        }
        return *this;
    }
    [[nodiscard]] bool checkHP() const { return viata > 0; }
    void takeDamage(const int damage) { viata -= damage; }

    ~Jucator() = default;
    friend std::ostream& operator<<(std::ostream& os, const Jucator& j) {
        return os << "Jucator[" << j.nume << "|HP:" << j.viata << "]";
    }
};

class Dinozaur {
    std::string nume;
    std::string tip;
    int agresivitate;  // 0-10
    int viata;

public:
    friend bool operator==(const Dinozaur& lhs, const Dinozaur& rhs)
    {
        return lhs.nume == rhs.nume
            && lhs.tip == rhs.tip
            && lhs.agresivitate == rhs.agresivitate
            && lhs.viata == rhs.viata;
    }

    friend bool operator!=(const Dinozaur& lhs, const Dinozaur& rhs)
    {
        return !(lhs == rhs);
    }

    Dinozaur(std::string nume, std::string tip, int agresivitate, int viata)
    : nume(std::move(nume)), tip(std::move(tip)), agresivitate(agresivitate), viata(viata) {}
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] const std::string& getTip() const { return tip; }
    [[nodiscard]] int getAgresivitate() const { return agresivitate; }
    [[nodiscard]] int getViata() const { return viata; }

    ~Dinozaur()=default;

    friend std::ostream& operator<<(std::ostream& os, const Dinozaur& d) {
        return os << "Dinozaur " << d.nume << " | Tip: " << d.tip << " | HP: "
                 << d.viata << " | Agresivitate: " << d.agresivitate <<std::endl;
    }
    [[nodiscard]] bool checkHP() const
    {
        return viata > 0;
    }
    void takeDamage(const int damage) { viata -= damage; }
};

class Arena {


    [[nodiscard]] static bool atacRateaza(int sansa) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 99);
        return dist(gen) < sansa;
    }

    static void atacSlab(Dinozaur& dino) {
        if (atacRateaza(20)) {
            std::cout << "Atacul jucatorului a dat gres!\n";
        } else {
            dino.takeDamage(5);
            std::cout << "Jucatorul a lovit dinozaurul!\n";
        }
    }

    static void atacPuternic(Dinozaur& dino) {
        if (atacRateaza(65)) {
            std::cout << "Atacul jucatorului a dat gres!\n";
        } else {
            dino.takeDamage(25);
            std::cout << "Jucatorul a lovit dinozaurul!\n";
        }
    }
    static void AfisHP(const Dinozaur& dino, const Jucator& jucator)
    {
        std::cout <<"Dino HP: " << dino.getViata() << std::endl;
        std::cout << "Jucator HP: " << jucator.getViata() << std::endl;
    }

public:


    static void startLupta(Dinozaur& dino, Jucator& jucator) {
        std::cout << "Lupta a inceput cu: " << dino << "\n";
        int alegere;

        while (jucator.checkHP() && dino.checkHP()) {
            AfisHP(dino, jucator);
            std::cout << "\nJucatorul ataca!\n";

            std::cout << "1. Atac slab\n2. Atac puternic\nAlege: ";
            std::cin >> alegere;

            if (alegere == 1) atacSlab(dino);
            else atacPuternic(dino);

            if (!dino.checkHP()) {
                std::cout << "Dinozaurul a fost invins!\n";
                break;
            }

            std::cout << "\nDinozaurul ataca!\n";

            if (atacRateaza(25)) {
                std::cout << "Atacul dinozaurului a dat gres!\n";
            } else {
                jucator.takeDamage(static_cast<int>(std::round(1.5 * dino.getAgresivitate())));
                std::cout << "Dinozaurul a lovit jucatorul!\n";

            }

            if (!jucator.checkHP()) {
                std::cout << "Jucatorul a fost invins!\n";
                break;
            }
        }
    }
};

class Game {

public:
    Game ()=default;

    static void run(std::vector<Dinozaur>& dinozauri, Jucator& jucator)
    {
        for (auto& dino : dinozauri)
        {
            if (!jucator.checkHP())
            {
                std::cout << "Jucatorul nu mai are viata!\n";
                break;
            }
            std::cout << "\nTe-ai intalnit cu: " << dino.getNume() << "\n";
            if (dino.getAgresivitate() >=8)
            {
                Arena::startLupta(dino,jucator);
            }
            else
            {
                std::cout << "Dialog cu dinozaurul:\n";
                if (dino.getAgresivitate() <=5)
                {
                    if (dino.getTip()=="Ierbivor")
                    {
                        std::cout << "alege de ignori sau sa vb(poti primii viata)\n";
                        std::cout << "ori +15hp ori dupa fiecare atac reusit +3" << std::endl;
                    }
                    else
                    {
                        std::cout << "vb sau te bati\n";
                    }

                }
                else
                {
                    if (dino.getTip()=="Carnivor")
                    {
                        std::cout << "vb si daca alegi ok nu te lupti(mai greu de evitat)\n";
                    }
                    else
                    {
                        std::cout<<"vb si daca alegi ok";
                    }
                }
            }
        }
    }
};

int main() {
    std::vector<Dinozaur> dinozauri = {
        {"T-Rex", "Carnivor", 10, 70}, {"Velociraptor", "Carnivor", 8, 50},
        {"Triceratops", "Ierbivor", 6, 50}, {"Stegosaurus", "Ierbivor", 5, 50},
        {"Spinosaurus", "Carnivor", 9, 50}, {"Brachiosaurus", "Ierbivor", 3, 50},
        {"Allosaurus", "Carnivor", 7, 50}, {"Pteranodon", "Carnivor", 6, 50},
        {"Ankylosaurus", "Ierbivor", 4, 50}, {"Dilophosaurus", "Carnivor", 7, 50},
        {"Iguanodon", "Ierbivor", 5, 50}, {"Compsognathus", "Carnivor", 3, 30},
        {"Parasaurolophus", "Ierbivor", 4, 30}, {"Carnotaurus", "Carnivor", 8, 50},
        {"Therizinosaurus", "Carnivor", 6, 50}
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(dinozauri.begin(), dinozauri.end(), gen);

    // Select primii 7 dinozauri
    std::vector<Dinozaur> selectie(dinozauri.begin(), dinozauri.begin() + 7);

    // Afis dinozaurii
    std::cout << "Dinozaurii selectati sunt:\n";
    for (const auto& dino : selectie) {
       std::cout << dino;
    }
    Jucator jucator("Jucator");

    Game::run(selectie,jucator);

    return 0;
}