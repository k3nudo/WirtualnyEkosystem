//
// Created by Użytkownik on 25.05.2025.
//

#include "mieszkaniec.h"

Mieszkaniec::Mieszkaniec(char _symbol) {
    symbol = _symbol;
}

Mieszkaniec::Mieszkaniec(const Mieszkaniec& mieszkaniec) {
    symbol = mieszkaniec.symbol;
}

char Mieszkaniec::jakiSymbol() const {
    return symbol;
}

Mieszkaniec::~Mieszkaniec() {
    // destruktor pusty
}
