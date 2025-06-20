#pragma once
#include "Dialog.h"

class DialogSession {
public:
    explicit DialogSession(const ArboreDialog& arbore);

    [[nodiscard]] const std::string& getMesaj() const;
    [[nodiscard]] const std::vector<Optiune>& getOptiuni() const;
    [[nodiscard]] bool isIncheiat() const;
    void selecteazaOptiune(int index);

private:
    const ArboreDialog& arbore;
    const NodDialog* nodCurent = nullptr;
    bool incheiat = false;

    void cautaNod(const std::string& id);
};
