#include "playable_character.h"

PlayableCharacter::PlayableCharacter() {
    reset_character();
}

void PlayableCharacter::reset_character() {
    this->lives = 3;
    this->direction = PlayerDirection::Left;
    this->score = 0;
}