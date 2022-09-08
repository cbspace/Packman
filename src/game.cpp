#include "game.h"

Game::Game() {
    quit_flag = false;
}

int Game::game_loop() {
    if(auto e = main_display.init()) {
        cout << e.value().get_error_string() << endl;
        return 1;
    }

    if (auto e = game_map.load_map_from_file(MAP_PATH)) {
        cout << e.value().get_error_string() << endl;
        return 1;
    }

    packman_character.pos.xgrid = game_map.get_player_start_x();
    packman_character.pos.ygrid = game_map.get_player_start_y();
    
    event_loop();
    
    return 0;
}

void Game::event_loop() {
    while (!quit_flag) {
        auto last_key_event = get_key();
        quit_flag = (last_key_event == KeyPress::Quit);

        render_cycle();

        SDL_Delay(20);
    }
}


void Game::render_cycle() {
    // Clear screen
    SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(main_display.main_renderer);

    // Draw screen
    draw_map();
    draw_objects();
    move_character(packman_character);

    // Update Screen
    SDL_RenderPresent(main_display.main_renderer);
}

void Game::move_character(Character &c) {

    if (c.direction == CharacterDirection::Left) {
        if (c.pos.xminor == 0) {
            if (next_square_is_space(c)) {
                c.pos.xgrid -= 1;
                c.pos.xminor = 19;
            }
        } else {
            c.pos.xminor -= 1;
        }
        
    }
    
    draw_character(c);
}

bool Game::next_square_is_space(Character& c) {
    if (c.direction == CharacterDirection::Left) {
        if (game_map.map_points[c.pos.ygrid][c.pos.xgrid-1] == MapPoint::Space) {
            return true;
        }
    }
    return false;
}

void Game::draw_character(Character &c) {
    SDL_Rect player_rect{ c.pos.xgrid * 20 - 7 + c.pos.xminor, c.pos.ygrid * 20 - 7 + c.pos.yminor, 34, 34 };
    SDL_SetRenderDrawColor(main_display.main_renderer, 0xea, 0xea, 0x00, 0xff);
    SDL_RenderFillRect(main_display.main_renderer, &player_rect);
}

void Game::draw_map() {
    int y = 0;
    for(const auto &row : game_map.map_points) {
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
            }
            x++;
        }
        y++;
    }
}

void Game::draw_objects() {
    int y = 0;
    for(const auto &row : game_map.map_objects) {
        int x = 0;
        for(const auto point : row) {
            if (point == MapObject::Dot) {
                SDL_Rect dot_rect{ x*20 + 8, y*20 + 8, 4, 4 };
                SDL_SetRenderDrawColor(main_display.main_renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_display.main_renderer, &dot_rect);
            } else if (point == MapObject::PowerPellet) {
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
