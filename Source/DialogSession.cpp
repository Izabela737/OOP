#include "../Header/DialogSession.h"

DialogSession::DialogSession(const ArboreDialog& arb) : arbore(arb) {
    cautaNod(arbore.start);
}

const std::string& DialogSession::getMesaj() const {
    return nodCurent->mesaj;
}

const std::vector<Optiune>& DialogSession::getOptiuni() const {
    return nodCurent->optiuni;
}

bool DialogSession::isIncheiat() const {
    return incheiat || nodCurent == nullptr;
}

void DialogSession::selecteazaOptiune(int index) {
    if (!nodCurent || index < 0 || static_cast<size_t>(index) >= nodCurent->optiuni.size()) return;

    std::string next = nodCurent->optiuni[index].next;

    if (next == "end") {
        incheiat = true;
    } else {
        cautaNod(next);
    }
}

void DialogSession::cautaNod(const std::string& id) {
    for (const NodDialog& n : arbore.noduri) {
        if (n.id == id) {
            nodCurent = &n;
            return;
        }
    }
    nodCurent = nullptr;
    incheiat = true;
}
