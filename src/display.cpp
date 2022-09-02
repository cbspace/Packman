#include "display.h"

Display::Display() {
    window = NULL;
    window_surface = NULL;
    main_renderer = NULL;
}

SDL_Window* Display::get_window() {
    return window;
}

optional<Error> Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return Error("SDL failed to initialise",SDL_GetError());
    }

    window = SDL_CreateWindow("Packman", 750, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) { return Error("SDL failed to initialise",SDL_GetError()); }

    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) { return Error("Cannot create SDL surface",SDL_GetError()); }

    main_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (main_renderer == NULL) { return Error("Cannot create SDL renderer",SDL_GetError()); }

    return nullopt;
}

Display::~Display() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(main_renderer);
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

void Display::draw_map() {
    int y = 0;
    SDL_Rect rect = { 0, 0 ,20, 20 };
    for(const auto &row : map_vec) {
        int x = 0;
        for(const auto point : row) {
            switch (point) {
                case MapPoint::Wall:
                    rect.x = x*20;
                    rect.y = y*20;
                    SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                    SDL_RenderFillRect(main_renderer, &rect);
                    break;
                case MapPoint::Space:
                    
                    break;
                case MapPoint::LeftOpening:
                    
                    break;
                case MapPoint::RightOpening:
                    
                    break;
                default:
                    cout << "Invalid character found in map file" << endl;
            }
            x++;
        }
        y++;
    }
}

void Display::render_cycle() {
    // Clear screen
    SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(main_renderer);
    SDL_RenderPresent(main_renderer);

    // Draw map
    draw_map();

    // Update Screen
    SDL_RenderPresent(main_renderer);
}