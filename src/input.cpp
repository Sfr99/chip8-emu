/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/

#include "chip8/input.hpp"
#include <stdexcept>

Input::Input() { keyboard.fill(false); }

void Input::setKey(uint8_t key, bool pressed) {
    if (key < 16)
        keyboard.at(key) = pressed;
    else
        throw std::invalid_argument("Value must be less than 16");
}

bool Input::getKey(uint8_t key) const {
    if (key < 16)
        return keyboard.at(key);
    else
        throw std::invalid_argument("Value must be less than 16");
}