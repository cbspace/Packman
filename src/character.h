#pragma once

#define CHARACTER_SIZE 34

namespace Packman {

enum class CharacterDirection {
    Up,
    Down,
    Left,
    Right,
    None
};

enum class CharacterName {
    Blinky,
    Winky,
    Inky,
    Clyde,
    PackMan
};

class Character {

    public:
        Character();
        void reset_character();
        void move_one();
        bool is_grid_aligned();    // Character in centre of square in x or y plane
        int absolute_position_x(); // x position used for rendering
        int absolute_position_y(); // y position used for rendering

        CharacterName name;
        CharacterDirection direction;

        int pos_grid_x;
        int pos_grid_y;

    protected:

        int pos_minor_x;
        int pos_minor_y;
        
};

}

using namespace Packman;