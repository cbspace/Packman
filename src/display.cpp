#include "display.h"

Pacman::Display::Display() {
    window = NULL;
    window_surface = NULL;
}

SDL_Window* Pacman::Display::get_window() {
    return window;
}

int Pacman::Display::init(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Pacman", 750, 300, width, height, 0);

    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    window_surface = SDL_GetWindowSurface(window);

    return 0;
}

Pacman::Display::~Display() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Pacman::Display::draw_map(std::string const &path) {
    std::ifstream ifs;
    std::string str;

    ifs.open("./res/maps/test.map", std::ios::in);

    if (ifs) {
        std::getline(ifs, str);
        std::cout << str << std::endl;
    }
    else { 
        std::cout << "Eror: Cannot open map file" << std::endl;
    }
    
    ifs.close();
}