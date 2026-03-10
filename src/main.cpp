/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#include "chip8/cpu.hpp"
#include "chip8/display.hpp"
#include "chip8/input.hpp"
#include "chip8/memory.hpp"
#include "chip8/renderer.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

const std::unordered_map<SDL_Keycode, uint8_t> keymap = {
    {SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3}, {SDLK_4, 0xC},
    {SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_r, 0xD},
    {SDLK_a, 0x7}, {SDLK_s, 0x8}, {SDLK_d, 0x9}, {SDLK_f, 0xE},
    {SDLK_z, 0xA}, {SDLK_x, 0x0}, {SDLK_c, 0xB}, {SDLK_v, 0xF},
};

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
    Input input;
    CPU cpu(memory, display, input);
    Renderer renderer(display);

    memory.loadROM(buffer.data(), buffer.size());

    while (true) {
        SDL_Delay(1000 / 60);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                auto it = keymap.find(event.key.keysym.sym);
                if (it != keymap.end()) {
                    input.setKey(it->second, event.type == SDL_KEYDOWN);
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            cpu.cycle();
        }

        cpu.updateTimers();
        renderer.render();
    }

    return 0;
}