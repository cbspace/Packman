#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

namespace Pacman {

class Game {
    public:
        Game();
        void event_loop();
    private:
};

}

#endif // GAME_H