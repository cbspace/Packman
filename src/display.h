#ifndef DISPLAY_H
#define DISPLAY_H

#include "lib/Error.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

using namespace std;

namespace Packman {

class Display {
    public:
        Display();
        SDL_Window* get_window();
        optional<Error> init(int width, int height);
        optional<Error> load_map_from_file(string const &path);

        virtual ~Display();

    private:
        SDL_Window* window;
        SDL_Surface* window_surface;
        int map_width = 0;
        int map_height = 0;
};

}

using namespace Packman;

#endif // DISPLAY_H