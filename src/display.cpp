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

    window = SDL_CreateWindow("Packman", 650, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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

    ifs.open(path, ios::in);
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
                    current_row[i++] = MapPoint::WallFull;
                    break;
                case 'A':
                    current_row[i++] = MapPoint::WallAbove;
                    break;
                case 'B':
                    current_row[i++] = MapPoint::WallBelow;
                    break;
                case 'L':
                    current_row[i++] = MapPoint::WallLeft;
                    break;
                case 'R':
                    current_row[i++] = MapPoint::WallRight;
                    break;
                case '1':
                    current_row[i++] = MapPoint::CornerTopLeftInside;
                    break;
                case '2':
                    current_row[i++] = MapPoint::CornerTopRightInside;
                    break;
                case '3':
                    current_row[i++] = MapPoint::CornerBottomRightInside;
                    break;
                case '4':
                    current_row[i++] = MapPoint::CornerBottomLeftInside;
                    break;
                case '5':
                    current_row[i++] = MapPoint::CornerTopLeftOutside;
                    break;
                case '6':
                    current_row[i++] = MapPoint::CornerTopRightOutside;
                    break;
                case '7':
                    current_row[i++] = MapPoint::CornerBottomRightOutside;
                    break;
                case '8':
                    current_row[i++] = MapPoint::CornerBottomLeftOutside;
                    break;
                case 'E':
                    current_row[i++] = MapPoint::Space;
                    break;
                case ' ':
                    current_row[i++] = MapPoint::Dot; //temp
                    break;
                case '[':
                    current_row[i++] = MapPoint::LeftOpening;
                    break;
                case ']':
                    current_row[i++] = MapPoint::RightOpening;
                    break;
                case 'P':
                    current_row[i++] = MapPoint::PowerPellet; //temp
                    break;
                default:
                    current_row[i++] = MapPoint::NotValid;
                    //cout << "Invalid character: '" << c << "' found in map file" << endl;
            } 
        });

        this->map_vec.push_back(current_row);
    }
    
    ifs.close();

    return nullopt;
}

void Display::draw_map() {
    int y = 0;
    for(const auto &row : map_vec) {
        int x = 0;
        for(const auto point : row) {
            if (point == MapPoint::WallFull) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 20 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::WallAbove) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::WallBelow) {
                SDL_Rect wall_rect{ x*20, y*20 + 10, 20, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::WallLeft) {
                SDL_Rect wall_rect{ x*20, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::WallRight) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopRightInside) {
                SDL_Rect wall_rect{ x*20, y*20 + 10 ,10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerBottomRightInside) {
                SDL_Rect wall_rect{ x*20,y*20 , 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerBottomLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerTopRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20 +10,10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerBottomRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerBottomLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_renderer, &wall_rect_small);
            } else if (point == MapPoint::Dot) {
                SDL_Rect dot_rect{ x*20 + 8, y*20 + 8, 4, 4 };
                SDL_SetRenderDrawColor(main_renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &dot_rect);
            } else if (point == MapPoint::PowerPellet) {
                SDL_Rect dot_rect{ x*20 + 6, y*20 + 6, 12, 12 };
                SDL_SetRenderDrawColor(main_renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_renderer, &dot_rect);
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