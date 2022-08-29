#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

namespace Pacman {

class Display {
    public:
        Display();
        SDL_Window* get_window();
        int init(int width, int height);
        virtual ~Display();

    private:
        SDL_Window* window;
        SDL_Surface* window_surface;
};

}

#endif // DISPLAY_H