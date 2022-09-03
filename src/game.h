#ifndef GAME_H
#define GAME_H

#include "lib/Error.h"
#include "display.h"
#include "playable_character.h"
#include <SDL2/SDL.h>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define MAP_PATH "./res/maps/map1.map"

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

class Game {

    public:
        Game();
        int game_loop();

        optional<Error> load_map_from_file(string const &path);
        
    private:
        void event_loop();
        void render_cycle();
        void draw_map();
        void update_character();
        optional<KeyPress> get_key();

        Display main_display;
        vector<vector<MapPoint>> map_vec;
        PlayableCharacter packman_character;

        bool quit_flag;
        int map_width = 0;
        int map_height = 0;
};

}

using namespace Packman;

#endif // GAME_H