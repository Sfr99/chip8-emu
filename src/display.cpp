/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/

#include "chip8/display.hpp"

Display::Display() { clear(); }

void Display::clear() { screen.fill(0); }

bool Display::draw(uint8_t x, uint8_t y, uint8_t size, const uint8_t *sprite) {
    bool colision = false;
    for (uint8_t i = 0; i < size; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if ((sprite[i] & (0x80 >> j)) != false) {
                bool before = screen[(y + i) % SCREEN_HEIGHT * SCREEN_WIDTH +
                                     (x + j) % SCREEN_WIDTH];
                screen[(y + i) % SCREEN_HEIGHT * SCREEN_WIDTH +
                       (x + j) % SCREEN_WIDTH] ^= 1;

                if (before) {
                    colision = true;
                }
            }
        }
    }
    return colision;
}