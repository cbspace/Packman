#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"

namespace Packman {

class PlayableCharacter : Character {

    public:
        PlayableCharacter();
        virtual ~PlayableCharacter();

        int lives;
        int score;
    private:

};

}

#endif // PLAYABLE_CHARACTER_H