/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#include "chip8/memory.hpp"
#include <algorithm>
#include <stdexcept>

Memory::Memory() { memory.fill(0); }

uint8_t Memory::read(uint16_t address) const {
    if (address < MEMORY_SIZE)
        return memory[address];
    else
        throw std::out_of_range("address out of RAM range");
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address < MEMORY_SIZE)
        memory[address] = value;
    else
        throw std::out_of_range("address out of RAM range");
}

void Memory::loadROM(const uint8_t *data, size_t size) {
    if (size <= MEMORY_SIZE - ROM_START_ADDRESS) {
        std::copy(data, data + size, memory.begin() + ROM_START_ADDRESS);
    } else
        throw std::out_of_range("ROM too large to fit in memory");
}

const uint8_t *Memory::adrPointer(uint16_t address) const {
    if (address < MEMORY_SIZE)
        return memory.data() + address;
    else
        throw std::out_of_range("address out of RAM range");
}
