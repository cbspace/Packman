#include <stdio.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "game.h"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 800

int main(int argc, char* argv[]) {
    Pacman::Display main_display;
    Pacman::Game pacman_game;

    // Init display and exit on error
    if(main_display.init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    // Run the game event loop
    pacman_game.event_loop();

    return 0;
}