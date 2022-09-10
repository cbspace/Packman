#pragma once

#include "character.h"

namespace Packman {

class PlayableCharacter : public Character {

    public:
        PlayableCharacter();
        void reset_character();
        bool requested_direction_is_opposite();

        int lives;
        int score;

        CharacterDirection requested_direction;
    private:

};

}

using namespace Packman;