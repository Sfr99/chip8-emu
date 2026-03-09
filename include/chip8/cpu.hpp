/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#ifndef CPU_HPP
#define CPU_HPP
#include "memory.hpp"

class CPU {
  private:
    // GP registers
    std::array<uint8_t, 16> gp_reg;

    // other registers
    uint16_t i_reg;
    uint16_t PC;

    // stack
    std::array<uint16_t, 16> stack;
    uint8_t SP;

    Memory &memory;

  public:
    CPU(Memory &_memory);

    void cycle();
};

#endif // CPU_HPP