#include "chip8/renderer.hpp"

Renderer::Renderer(Display &_display) : display(_display) {
    SDL_Init(SDL_INIT_VIDEO);

    window =
        SDL_CreateWindow("chip8-emu", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, Display::SCREEN_WIDTH * scale,
                         Display::SCREEN_HEIGHT * scale, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (uint8_t i = 0; i < Display::SCREEN_HEIGHT; i++) {
        for (uint8_t j = 0; j < Display::SCREEN_WIDTH; j++) {
            if (display.getPixel(j, i)) {
                SDL_Rect rect = {j * scale, i * scale, scale, scale};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}