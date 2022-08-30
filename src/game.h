#ifndef GAME_H
#define GAME_H

#include "display.h"
#include <SDL2/SDL.h>
#include <optional>

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 800
#define MAP_PATH "../res/maps/test.map"

using namespace std;

namespace Pacman {

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
        Pacman::Display main_display;
        bool quit_flag;
        optional<KeyPress> get_key();
};

}

#endif // GAME_H