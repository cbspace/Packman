#pragma once

#include "LibCB/Error.h"
#include "display.h"
#include "game_map.h"
#include "playable_character.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <vector>

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
        void draw_objects();
        void move_character(PlayableCharacter& c);
        void draw_character(Character& c);
        void process_key_event();
        void check_collisions(PlayableCharacter& c);

        bool next_square_is(MapPoint match_square_type, Character& c, CharacterDirection dir_to_check);
        bool try_change_direction(PlayableCharacter& c);
        bool character_tunnel_movement(Character& c);

        Display main_display;
        GameMap game_map;
        
        PlayableCharacter packman_character;

        bool quit_flag;

};

}

using namespace Packman;