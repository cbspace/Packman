#pragma once

#include "lib/Error.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>

#define WINDOW_WIDTH  560
#define WINDOW_HEIGHT 620

using std::optional;
using std::nullopt;

namespace Packman {

class Display {

    public:
        Display();
        virtual ~Display();

        optional<Error> init();
        SDL_Window* get_window();

        SDL_Window* window;
        SDL_Surface* window_surface;
        SDL_Renderer* main_renderer;
};

}

using namespace Packman;