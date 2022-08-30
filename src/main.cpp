#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"

int main(int argc, char* argv[]) {
    Pacman::Game pacman_game;

    return pacman_game.game_loop();
}