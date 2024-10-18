#include "display.h"

Display::Display() {
    window = nullptr;
    main_renderer = nullptr;
}

optional<Error> Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return Error("SDL failed to initialise",SDL_GetError());
    }

    window = shared_ptr<SDL_Window>(SDL_CreateWindow("Packman", 650, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0), SDL_DestroyWindow);
    if (window == nullptr) { return Error("SDL failed to initialise", SDL_GetError()); }

    main_renderer = shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (main_renderer == nullptr) { return Error("Cannot create SDL renderer", SDL_GetError()); }

    return nullopt;
}

SDL_Renderer* Display::get_renderer() {
    return main_renderer.get();
}

Display::~Display() {
    SDL_Quit();
}