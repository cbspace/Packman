#include "playable_character.h"

PlayableCharacter::PlayableCharacter() {
    reset_character();
}

void PlayableCharacter::reset_character() {
    this->lives = 3;
    this->direction = CharacterDirection::None;
    this->requested_direction = CharacterDirection::None;
    this->score = 0;
}

bool PlayableCharacter::requested_direction_is_opposite() {
    if (direction == CharacterDirection::Left && requested_direction == CharacterDirection::Right)
        return true;

    if (direction == CharacterDirection::Right && requested_direction == CharacterDirection::Left)
        return true;

    if (direction == CharacterDirection::Up && requested_direction == CharacterDirection::Down)
        return true;

    if (direction == CharacterDirection::Down && requested_direction == CharacterDirection::Up)
        return true;

    return false;
}