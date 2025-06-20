#include "../Header/DialogManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <random>

using json = nlohmann::json;

void DialogManager::incarcaDinFisier(const std::string& path) {
    std::ifstream f(path);
    json j;
    f >> j;

    for (auto& [tip, lista] : j.items()) {
        for (auto& d : lista) {
            ArboreDialog arbore;
            arbore.start = d["start"];
            for (auto& nod : d["noduri"]) {
                NodDialog n;
                n.id = nod["id"];
                n.mesaj = nod["mesaj"];
                for (auto& opt : nod["optiuni"]) {
                    n.optiuni.push_back({ opt["text"], opt["next"] });
                }
                arbore.noduri.push_back(n);
            }
            dialoguri[tip].push_back(arbore);
        }
    }
}

const ArboreDialog& DialogManager::alegeRandom(const std::string& tip) {
    auto& lista = dialoguri[tip];
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, lista.size() - 1);
    return lista[dist(gen)];
}
