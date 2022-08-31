#include "display.h"

Display::Display() {
    window = NULL;
    window_surface = NULL;
}

SDL_Window* Display::get_window() {
    return window;
}

optional<Error> Display::init(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        string error_message = "SDL failed to initialise: ";
        error_message += SDL_GetError();
        return Error(error_message);
    }

    window = SDL_CreateWindow("Pacman", 750, 300, width, height, 0);

    if (window == NULL) {
        string error_message = "SDL failed to initialise: ";
        error_message += SDL_GetError();
        return Error(error_message);
    }

    window_surface = SDL_GetWindowSurface(window);

    return nullopt;
}

Display::~Display() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

optional<Error> Display::load_map_from_file(string const &path) {
    ifstream ifs;
    string str;

    ifs.open("./res/maps/test.map", ios::in);

    if (!ifs) { return Error("Could not open map file"); }

    getline(ifs,str);
    int map_width = stoi(str);
    getline(ifs,str);
    int map_height = stoi(str);

    while(!ifs.eof()) {
        getline(ifs, str);
        cout << str << endl;
    }
    
    ifs.close();

    return nullopt;
}