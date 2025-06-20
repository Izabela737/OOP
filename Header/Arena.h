#pragma once
#include "Dinozaur.h"
#include "Jucator.h"

class Arena {

    static bool inLupta;

public:
    static void startLupta(const Dinozaur& dino) ;
    static bool procesTuraJucator(int atac, Dinozaur& dino, Jucator& jucator);
    static bool eLuptaInDesfasurare();
    static void reset();
    static void atacSlab(Dinozaur& dino, Jucator& jucator);
    static void atacPuternic(Dinozaur& dino) ;
    static bool atacRateaza(int sansa);
};