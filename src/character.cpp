#include "character.h"

Character::Character() {
    reset_character();
}

void Character::move_one() {
    if (direction == CharacterDirection::Left) {
        if (pos_minor_x == 0) {
            pos_grid_x -= 1;
            pos_minor_x = MINOR_STEP_MAX;
        } else {
            pos_minor_x -= 1;
        }
    } else if (direction == CharacterDirection::Right) {
        if (pos_minor_x == MINOR_STEP_MAX) {
            pos_grid_x += 1;
            pos_minor_x = 0;
        } else {
            pos_minor_x += 1;
        }
    } if (direction == CharacterDirection::Up) {
        if (pos_minor_y == 0) {
            pos_grid_y -= 1;
            pos_minor_y = MINOR_STEP_MAX;
        } else {
            pos_minor_y -= 1;
        }
    } else if (direction == CharacterDirection::Down) {
        if (pos_minor_y == MINOR_STEP_MAX) {
            pos_grid_y += 1;
            pos_minor_y = 0;
        } else {
            pos_minor_y += 1;
        }
    }
}

void Character::reset_character() {
    pos_minor_x = 0;
    pos_minor_y = 0;
    is_in_tunnel = false;
}

// Character in centre of square in x or y plane
bool Character::is_grid_aligned() {
    if (direction == CharacterDirection::Left || direction == CharacterDirection::Right)
        return pos_minor_x == 0;

    if (direction == CharacterDirection::Up || direction == CharacterDirection::Down)
        return pos_minor_y == 0;
    
    return false;
}

// x position used for rendering
int Character::absolute_position_x() {
    return pos_grid_x * 20 + pos_minor_x * MOVE_STEP - ((CHARACTER_SIZE - 20) / 2);
}

// y position used for rendering
int Character::absolute_position_y() {
    return pos_grid_y * 20 + pos_minor_y * MOVE_STEP - ((CHARACTER_SIZE - 20) / 2);
}
