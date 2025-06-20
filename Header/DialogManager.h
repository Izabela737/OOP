#pragma once
#include "Dialog.h"
#include <unordered_map>

class DialogManager {
public:
    void incarcaDinFisier(const std::string& path);
    const ArboreDialog& alegeRandom(const std::string& tip);
private:
    std::unordered_map<std::string, std::vector<ArboreDialog>> dialoguri;
};
