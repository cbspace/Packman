#include "character.h"

Character::Character() {
    reset_character();
}

void Character::reset_character() {
    pos.xminor = 9;
    pos.yminor = 9;
}