#ifndef CHARACTER_H
#define CHARACTER_H

namespace Packman {

enum class PlayerDirection {
    Up,
    Down,
    Left,
    Right
};

class Character {

    public:
        Character();

        void reset_character();

        int x_pos;
        int y_pos;
        PlayerDirection direction;

    protected:
    
    private:

};

}

using namespace Packman;

#endif // CHARACTER_H