#include "character.h"

Character::Character() {
    reset_character();
}

void Character::reset_character() {
    pos.xminor = 0;
    pos.yminor = 0;
}