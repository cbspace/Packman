#include "display.h"

Display::Display() {
    window = NULL;
    window_surface = NULL;
    main_renderer = NULL;
}

SDL_Window* Display::get_window() {
    return window;
}

optional<Error> Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return Error("SDL failed to initialise",SDL_GetError());
    }

    window = SDL_CreateWindow("Packman", 650, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) { return Error("SDL failed to initialise",SDL_GetError()); }

    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) { return Error("Cannot create SDL surface",SDL_GetError()); }

    main_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (main_renderer == NULL) { return Error("Cannot create SDL renderer",SDL_GetError()); }

    return nullopt;
}

Display::~Display() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(main_renderer);
    SDL_Quit();
}