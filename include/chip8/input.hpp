/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#ifndef INPUT_HPP
#define INPUT_HPP

#include <array>
#include <cstdint>

class Input {
  private:
    std::array<bool, 16> keyboard; // true->is pressed

  public:
    Input();
    void setKey(uint8_t key, bool pressed);
    bool getKey(uint8_t key) const;
};

#endif // INPUT_HPP