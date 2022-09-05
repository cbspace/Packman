#ifndef GAME_H
#define GAME_H

#include "lib/Error.h"
#include "display.h"
#include "game_map.h"
#include "playable_character.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <vector>
//#include <algorithm>

#define MAP_PATH "./res/maps/map1.map"

using std::cout;
using std::endl;
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
        
    private:
        void event_loop();
        void render_cycle();
        void draw_map();
        void update_character();
        optional<KeyPress> get_key();

        Display main_display;
        GameMap game_map;
        
        PlayableCharacter packman_character;

        bool quit_flag;
        // int map_width = 0;
        // int map_height = 0;


};

}

using namespace Packman;

#endif // GAME_H