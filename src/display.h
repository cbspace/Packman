#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

namespace Pacman {

class Display {
    public:
        Display();
        SDL_Window* get_window();
        int init(int width, int height);

        void draw_map(std::string const &path);

        virtual ~Display();

    private:
        SDL_Window* window;
        SDL_Surface* window_surface;
};

}

#endif // DISPLAY_H