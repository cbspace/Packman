#ifndef DISPLAY_H
#define DISPLAY_H

#include "lib/Error.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace Packman {

enum class MapPoint {
    Wall,
    Space,
    LeftOpening,
    RightOpening
};

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
        vector<vector<MapPoint>> map_vec;
};

}

using namespace Packman;

#endif // DISPLAY_H