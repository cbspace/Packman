#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <optional>

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
        void event_loop();
    private:
        bool quit_flag;
        optional<KeyPress> get_key();
};

}

#endif // GAME_H