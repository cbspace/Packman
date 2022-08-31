#ifndef GAME_H
#define GAME_H

#include "display.h"
#include <SDL2/SDL.h>
#include <optional>
#include <iostream>

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 800
#define MAP_PATH "../res/maps/test.map"

using std::optional;

namespace Packman {

enum class KeyPress {
    Up,
    Down,
    Left,
    Right,
    Pause,
    Quit
};

class Game {
    public:
        Game();
        int game_loop();
        int event_loop();
    private:
        Packman::Display main_display;
        bool quit_flag;
        optional<KeyPress> get_key();
};

}

using namespace Packman;

#endif // GAME_H