#pragma once
#include <string>
#include <vector>

struct Optiune {
    std::string text;
    std::string next;
};

struct NodDialog {
    std::string id;
    std::string mesaj;
    std::string speaker = "NPC";
    std::vector<Optiune> optiuni;
};

struct ArboreDialog {
    std::string start;
    std::vector<NodDialog> noduri;
};
