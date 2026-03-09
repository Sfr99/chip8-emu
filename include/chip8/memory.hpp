/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <array>
#include <cstddef>
#include <cstdint>

class Memory {
  public:
    static constexpr size_t MEMORY_SIZE = 4096;
    static constexpr size_t ROM_START_ADDRESS = 0x200;

    Memory();
    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);
    void loadROM(const uint8_t *data, size_t size);

  private:
    std::array<uint8_t, MEMORY_SIZE> memory;
};

#endif // MEMORY_HPP