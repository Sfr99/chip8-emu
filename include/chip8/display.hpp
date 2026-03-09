/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <array>
#include <cstdint>

class Display {
  public:
    Display();
    void clear();
    bool draw(uint8_t x, uint8_t y, uint8_t size, const uint8_t *sprite);
    static constexpr uint8_t SCREEN_WIDTH = 64;
    static constexpr uint8_t SCREEN_HEIGHT = 32;
    bool getPixel(uint8_t x, uint8_t y) const;

  private:
    std::array<bool, SCREEN_WIDTH * SCREEN_HEIGHT> screen;
};
#endif // DISPLAY_HPP