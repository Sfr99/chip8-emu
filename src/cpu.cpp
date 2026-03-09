#include "chip8/cpu.hpp"

CPU::CPU(Memory &_memory) : memory(_memory) {
    PC = Memory::ROM_START_ADDRESS;
    SP = 0;
    i_reg = 0;
    stack.fill(0);
    gp_reg.fill(0);
}

void CPU::cycle() {
    // fetch
    uint16_t opcode = memory.read(PC) << 8 | memory.read(PC + 1);
    PC += 2;

    // decode
    uint8_t decode = (opcode & 0xF000) >> 12;

    switch (decode) {
    case 0x6: {
        // load in register: 0x6XNN -> writes value NN in register X
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = (opcode & 0x00FF);
        gp_reg[x] = nn;
        break;
    }
    default:
        break;
    }
}