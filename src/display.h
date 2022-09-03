#ifndef DISPLAY_H
#define DISPLAY_H

#include "lib/Error.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define WINDOW_WIDTH  560
#define WINDOW_HEIGHT 620

using namespace std;

namespace Packman {

enum class MapPoint {
    WallFull,
    WallAbove,
    WallBelow,
    WallLeft,
    WallRight,
    CornerTopLeftInside,
    CornerTopRightInside,
    CornerBottomLeftInside,
    CornerBottomRightInside,
    CornerTopLeftOutside,
    CornerTopRightOutside,
    CornerBottomLeftOutside,
    CornerBottomRightOutside,
    Space,
    LeftOpening,
    RightOpening,
    Dot,
    PowerPellet,
    NotValid
};

class Display {

    public:
        Display();
        virtual ~Display();

        optional<Error> init();
        optional<Error> load_map_from_file(string const &path);
        
        void render_cycle();
        void draw_map();
        void update_character();

    private:
        SDL_Window* window;
        SDL_Surface* window_surface;
        SDL_Renderer* main_renderer;

        int map_width = 0;
        int map_height = 0;
        vector<vector<MapPoint>> map_vec;

        SDL_Window* get_window();

};

}

using namespace Packman;

#endif // DISPLAY_H