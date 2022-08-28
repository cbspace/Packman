#include <stdio.h>
#include <SDL2/SDL.h>
#include "display.h"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 800

int main(int argc, char* argv[]) {
    Display main_display;

    // Init display and exit on error
    if(main_display.init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return 1;
    }

    SDL_Delay(3000);

    return 0;
}