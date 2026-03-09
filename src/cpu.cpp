/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/

#include "chip8/cpu.hpp"

CPU::CPU(Memory &_memory, Display &_display)
    : memory(_memory), display(_display) {
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

    // execute

    switch (decode) {
    case 0x0: {
        switch (opcode & 0x000F) {
        case 0x0:
            // 0x00E0 clear display screen
            display.clear();
            break;
        case 0xE:
            // 0x00EE
            break;
        default:
            break;
        }
        break;
    }
    case 0x1: {
        // jump: 0x1NNN -> jump to address NNN
        uint16_t nnn = (opcode & 0x0FFF);
        PC = nnn;
        break;
    }
    case 0x6: {
        // load in register: 0x6XNN -> writes value NN in register X
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = (opcode & 0x00FF);
        gp_reg[x] = nn;
        break;
    }
    case 0x7: {
        // add value to register: 0x7XNN -> adds value NN to register X
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = (opcode & 0x00FF);
        gp_reg[x] += nn;
        break;
    }
    case 0x8: {
        // aritmethic and logical operations
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;
        switch (opcode & 0x000F) {
        // Logical
        case 0x0:
            // set: 0x8XY0 -> set vy value to vx
            gp_reg[x] = gp_reg[y];
            break;
        case 0x1:
            // Binary OR: 0x8XY1 -> vx = vx OR vy
            gp_reg[x] |= gp_reg[y];
            break;
        case 0x2:
            // Binary AND: 0x8XY2 -> vx = vx AND vy
            gp_reg[x] &= gp_reg[y];
            break;
        case 0x3:
            // Binary XOR: 0x8XY3 -> vx = vx XOR vy
            gp_reg[x] ^= gp_reg[y];
            break;
        // Arithmetic
        case 0x4: {
            // Add: 0x8XY4 -> vx = vx + vy
            uint16_t sum = gp_reg[x] + gp_reg[y];
            gp_reg[x] = sum & 0xFF;
            gp_reg[0xF] = (sum > 255) ? 1 : 0;
            break;
        }
        case 0x5: {
            // Sub: 0x8XY5 -> vx = vx - vy
            uint8_t flag = (gp_reg[x] >= gp_reg[y]) ? 1 : 0;
            gp_reg[x] -= gp_reg[y];
            gp_reg[0xF] = flag;
            break;
        }
        case 0x6: {
            // Shift right: 0x8XY6
            uint8_t flag = gp_reg[x] & 0x1;
            gp_reg[x] >>= 1;
            gp_reg[0xF] = flag;
            break;
        }
        case 0x7: {
            // Sub: 0x8XY7 -> vx = vy - vx
            uint8_t flag = (gp_reg[y] >= gp_reg[x]) ? 1 : 0;
            gp_reg[x] = gp_reg[y] - gp_reg[x];
            gp_reg[0xF] = flag;
            break;
        }
        case 0xE: {
            // Shift left: 0x8XYE
            uint8_t flag = (gp_reg[x] >> 7) & 0x1;
            gp_reg[x] <<= 1;
            gp_reg[0xF] = flag;
            break;
        }
        default:
            break;
        }
        break;
    }
    case 0xA: {
        // set index register: 0xANNN -> set index register to NNN
        uint16_t nnn = (opcode & 0x0FFF);
        i_reg = nnn;
        break;
    }
    case 0xD: {
        // draw display screen: draw from vx to vy draw an N pixels tall
        // sprite from the memory location that the I index register is
        // holding to the screen, at the horizontal X coordinate in VX
        // and the Y coordinate in VY
        if (display.draw(gp_reg[(opcode & 0x0F00) >> 8],
                         gp_reg[(opcode & 0x00F0) >> 4], (opcode & 0x000F),
                         memory.adrPointer(i_reg)))
            gp_reg[15] = 1;

        break;
    }
    default:
        break;
    }
}