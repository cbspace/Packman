#pragma once

#include "LibCB/Error.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <memory>

#define WINDOW_WIDTH  560
#define WINDOW_HEIGHT 620

using std::optional;
using std::nullopt;
using std::shared_ptr;
using std::make_shared;

namespace Packman {

class Display {

    public:
        Display();
        virtual ~Display();

        optional<Error> init();
        SDL_Renderer* get_renderer();

        shared_ptr<SDL_Window> window;
        shared_ptr<SDL_Renderer> main_renderer;
};

}

using namespace Packman;