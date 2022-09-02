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
    int map_width = (str.find_first_not_of("0123456789") == string::npos && !str.empty()) ? stoi(str) : 0;
    getline(ifs,str);
    int map_height = (str.find_first_not_of("0123456789") == string::npos && !str.empty()) ? stoi(str) : 0;
    if (!map_width || !map_height || !(map_width + map_height < 200)) { return Error("Invalid map size"); }

    while(!ifs.eof()) {
        vector<MapPoint> current_row(map_width);
        getline(ifs, str);
        int i = 0;

        for_each(str.begin(), str.end(), [&current_row, &i] (char const &c) {
            switch (c) {
                case '*':
                    current_row[i++] = MapPoint::Wall;
                    break;
                case ' ':
                    current_row[i++] = MapPoint::Space;
                    break;
                case '1':
                    current_row[i++] = MapPoint::LeftOpening;
                    break;
                case '2':
                    current_row[i++] = MapPoint::RightOpening;
                    break;
                default:
                    current_row[i++] = MapPoint::Invalid;
                    cout << "Invalid character: '" << c << "' found in map file" << endl;
            } 
        });

        this->map_vec.push_back(current_row);
    }
    
    ifs.close();

    return nullopt;
}