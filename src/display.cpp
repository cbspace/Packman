#include "display.h"

Display::Display() {
    window = NULL;
}

SDL_Window* Display::get_window() {
    return window;
}

int Display::init(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "Pacman",
        750,
        300,
        width,
        height,
        0);

    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

Display::~Display() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}