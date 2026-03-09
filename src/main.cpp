/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#include "chip8/cpu.hpp"
#include "chip8/display.hpp"
#include "chip8/memory.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chip8-emu <rom>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM: " << argv[1] << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    file.read(reinterpret_cast<char *>(buffer.data()), size);

    Memory memory;
    Display display;
    CPU cpu(memory, display);

    memory.loadROM(buffer.data(), buffer.size());

    while (true) {
        cpu.cycle();
    }

    return 0;
}