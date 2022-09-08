#include "playable_character.h"

PlayableCharacter::PlayableCharacter() {
    reset_character();
}

void PlayableCharacter::reset_character() {
    this->lives = 3;
    this->direction = CharacterDirection::None;
    this->score = 0;
}