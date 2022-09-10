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

    packman_character.pos_grid_x = game_map.get_player_start_x();
    packman_character.pos_grid_y = game_map.get_player_start_y();
    
    event_loop();
    
    return 0;
}

void Game::event_loop() {
    while (!quit_flag) {
        process_key_event();
        render_cycle();

        SDL_Delay(16);
    }
}


void Game::render_cycle() {
    SDL_SetRenderDrawColor(main_display.main_renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(main_display.main_renderer);

    draw_map();
    draw_objects();
    move_character(packman_character);
    draw_character(packman_character);

    SDL_RenderPresent(main_display.main_renderer);
}

bool Game::try_change_direction(PlayableCharacter& c) {
    if (c.requested_direction == CharacterDirection::None)
        return false;

    if (c.requested_direction == c.direction) {
        c.requested_direction = CharacterDirection::None;
        return false;
    }

    if (next_square_is_space(c,c.requested_direction)) {
        c.direction = c.requested_direction;
        c.requested_direction = CharacterDirection::None;
        return true;
    }

    return false;
}

void Game::move_character(PlayableCharacter &c) {
    // FIXME: should check for grid alignment and/or next square free
    if (c.direction == CharacterDirection::None && c.requested_direction != CharacterDirection::None) {
        c.direction = c.requested_direction;
    }
    
    if (c.is_grid_aligned()) {
        if (!try_change_direction(c) && next_square_is_space(c, c.direction)) {
            c.move_one();
        }
    } else {
        if (c.requested_direction_is_opposite()) {
            c.direction = c.requested_direction;
        } else {
            c.move_one();
        }
    }
}

bool Game::next_square_is_space(Character& c, CharacterDirection dir_to_check) {
    if (dir_to_check == CharacterDirection::Left) {
        if (game_map.map_points[c.pos_grid_y][c.pos_grid_x - 1] == MapPoint::Space) {
            return true;
        }
    } else if (dir_to_check == CharacterDirection::Right) {
        if (game_map.map_points[c.pos_grid_y][c.pos_grid_x + 1] == MapPoint::Space) {
            return true;
        }
    } if (dir_to_check == CharacterDirection::Up) {
        if (game_map.map_points[c.pos_grid_y - 1][c.pos_grid_x] == MapPoint::Space) {
            return true;
        }
    } else if (dir_to_check == CharacterDirection::Down) {
        if (game_map.map_points[c.pos_grid_y + 1][c.pos_grid_x] == MapPoint::Space) {
            return true;
        }
    }

    return false;
}

void Game::draw_character(Character &c) {
    SDL_Rect player_rect{ c.absolute_position_x(), c.absolute_position_y(), 34, 34 };
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


void Game::process_key_event() {
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit_flag = true;
        } else if (event.type == SDL_KEYDOWN) {
            auto key = event.key.keysym.scancode;
            if (key == SDL_SCANCODE_ESCAPE || key == SDL_SCANCODE_Q) {
                quit_flag = true;
            } else if (key == SDL_SCANCODE_UP) {
                packman_character.requested_direction = CharacterDirection::Up; 
            } else if (key == SDL_SCANCODE_DOWN) {
                packman_character.requested_direction = CharacterDirection::Down;
            } else if (key == SDL_SCANCODE_LEFT) {
                packman_character.requested_direction = CharacterDirection::Left;
            } else if (key == SDL_SCANCODE_RIGHT) {
                packman_character.requested_direction = CharacterDirection::Right;
            }
        }
    }
}
