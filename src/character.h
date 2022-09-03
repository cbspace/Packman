#ifndef CHARACTER_H
#define CHARACTER_H

namespace Packman {

class Character {

    public:
        Character();
        virtual ~Character();

        void reset_character();

        int x_pos;
        int y_pos;
    private:

};

}

#endif // CHARACTER_H