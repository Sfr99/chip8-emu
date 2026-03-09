/* chip8-emu -- MIT License -- Javier Salafranca Pradilla -- 2026*/
#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "display.hpp"
#include <SDL2/SDL.h>

class Renderer {
  public:
    Renderer(Display &_display);
    ~Renderer();

    void render();

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Display &display;

    static constexpr uint8_t scale = 10;
};

#endif // RENDERER_HPP