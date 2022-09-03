#include "game.h"

Game::Game() {
    quit_flag = false;
}

int Game::game_loop() {
    if(auto e = main_display.init()) {
        cout << e.value().get_error_string() << endl;
        return 1;
    }

    if (auto e = load_map_from_file(MAP_PATH)) {
        cout << e.value().get_error_string() << endl;
        return 1;
    }

    event_loop();

    return 0;
}

void Game::event_loop() {
    while (!quit_flag) {
        auto last_key_event = get_key();
        quit_flag = (last_key_event == KeyPress::Quit);

        render_cycle();

        SDL_Delay(16);
    }
}


void Game::render_cycle() {
    // Clear screen
    SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(main_display.main_renderer);

    // Draw screen
    draw_map();
    update_character();

    // Update Screen
    SDL_RenderPresent(main_display.main_renderer);
}

void Game::update_character() {

}

void Game::draw_map() {
    int y = 0;
    for(const auto &row : map_vec) {
        int x = 0;
        for(const auto point : row) {
            if (point == MapPoint::WallFull) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 20 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::WallAbove) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::WallBelow) {
                SDL_Rect wall_rect{ x*20, y*20 + 10, 20, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::WallLeft) {
                SDL_Rect wall_rect{ x*20, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::WallRight) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopRightInside) {
                SDL_Rect wall_rect{ x*20, y*20 + 10 ,10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerBottomRightInside) {
                SDL_Rect wall_rect{ x*20,y*20 , 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerBottomLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect);
            } else if (point == MapPoint::CornerTopLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerTopRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20 +10,10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerBottomRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_small);
            } else if (point == MapPoint::CornerBottomLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.main_renderer, &wall_rect_small);
            } else if (point == MapPoint::Dot) {
                SDL_Rect dot_rect{ x*20 + 8, y*20 + 8, 4, 4 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &dot_rect);
            } else if (point == MapPoint::PowerPellet) {
                SDL_Rect dot_rect{ x*20 + 6, y*20 + 6, 12, 12 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &dot_rect);
            }
            x++;
        }
        y++;
    }
}

optional<KeyPress> Game::get_key() {
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return KeyPress::Quit;
        } else if (event.type == SDL_KEYDOWN) {
            auto key = event.key.keysym.scancode;
            if (key == SDL_SCANCODE_ESCAPE || key == SDL_SCANCODE_Q) {
                return KeyPress::Quit;
            }
            else if (key == SDL_SCANCODE_UP) {
                return KeyPress::Up;
            }
            if (key == SDL_SCANCODE_DOWN) {
                return KeyPress::Down;
            }
            if (key == SDL_SCANCODE_LEFT) {
                return KeyPress::Left;
            }
            if (key == SDL_SCANCODE_RIGHT) {
                return KeyPress::Right;
            }
        }
    }

    return nullopt;
}

optional<Error> Game::load_map_from_file(string const &path) {
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
