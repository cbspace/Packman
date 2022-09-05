#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"

namespace Packman {

class PlayableCharacter : Character {

    public:
        PlayableCharacter();
        void reset_character();

        int lives;
        int score;
    private:

};

}

using namespace Packman;

#endif // PLAYABLE_CHARACTER_H