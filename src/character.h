#ifndef CHARACTER_H
#define CHARACTER_H

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

struct CharacterPos {
    int xgrid;
    int ygrid;
    int xminor;
    int yminor;
};

class Character {

    public:
        Character();
        void reset_character();

        CharacterName name;
        CharacterDirection direction;
        CharacterPos pos;
        
    protected:
    
    private:

};

}

using namespace Packman;

#endif // CHARACTER_H