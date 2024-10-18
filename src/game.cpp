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
        move_character(packman_character);
        check_collisions(packman_character);

        render_cycle();
        SDL_Delay(22);
    }
}


void Game::render_cycle() {
    SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(main_display.get_renderer());

    draw_map();
    draw_objects();
    draw_character(packman_character);

    SDL_RenderPresent(main_display.get_renderer());
}

bool Game::try_change_direction(PlayableCharacter& c) {
    if (c.requested_direction == CharacterDirection::None)
        return false;

    if (c.requested_direction == c.direction) {
        c.requested_direction = CharacterDirection::None;
        return false;
    }

    if (next_square_is(MapPoint::Space, c,c.requested_direction)) {
        c.direction = c.requested_direction;
        c.requested_direction = CharacterDirection::None;
        return true;
    }

    return false;
}

//FIXME: Can get stuck when changing direction in tunnel
bool Game::character_tunnel_movement(Character& c) {
    if (c.is_in_tunnel) {
        if (c.direction == CharacterDirection::Left) {
            if (c.pos_minor_x <= -13) {
                c.pos_grid_x = game_map.get_right_tunnel_location_x();
                c.reset_character();
                c.is_in_tunnel = false;
            } else {
                c.pos_minor_x -= MOVE_STEP;
            }
        } else if (c.direction == CharacterDirection::Right) {
            if (c.pos_minor_x >= 13) {
                c.pos_grid_x = game_map.get_left_tunnel_location_x();
                c.reset_character();
                c.is_in_tunnel = false;
            } else {
                c.pos_minor_x += MOVE_STEP;
            }
        }
        return true;
    } 

    return false;
}

void Game::move_character(PlayableCharacter &c) {
    // FIXME: should check for grid alignment and/or next square free
    if (c.direction == CharacterDirection::None && c.requested_direction != CharacterDirection::None) {
        c.direction = c.requested_direction;
    }

    if (character_tunnel_movement(c)) {
        return;
    }
    
    if (c.is_grid_aligned()) {
        try_change_direction(c);
        if (next_square_is(MapPoint::Space, c, c.direction)) { 
            c.move_one(); 
        } else if (next_square_is(MapPoint::LeftOpening, c, c.direction) || next_square_is(MapPoint::RightOpening, c, c.direction)) { 
            c.is_in_tunnel = true;
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

bool Game::next_square_is(MapPoint match_square_type, Character& c, CharacterDirection dir_to_check) {
    if (dir_to_check == CharacterDirection::Left) {
        if (game_map.map_points[c.pos_grid_y][c.pos_grid_x - 1] == match_square_type) {
            return true;
        }
    } else if (dir_to_check == CharacterDirection::Right) {
        if (game_map.map_points[c.pos_grid_y][c.pos_grid_x + 1] == match_square_type) {
            return true;
        }
    } if (dir_to_check == CharacterDirection::Up) {
        if (game_map.map_points[c.pos_grid_y - 1][c.pos_grid_x] == match_square_type) {
            return true;
        }
    } else if (dir_to_check == CharacterDirection::Down) {
        if (game_map.map_points[c.pos_grid_y + 1][c.pos_grid_x] == match_square_type) {
            return true;
        }
    }

    return false;
}

void Game::draw_character(Character &c) {
    SDL_Rect player_rect{ c.absolute_position_x(), c.absolute_position_y(), 34, 34 };
    SDL_SetRenderDrawColor(main_display.get_renderer(), 0xea, 0xea, 0x00, 0xff);
    SDL_RenderFillRect(main_display.get_renderer(), &player_rect);
}

void Game::draw_map() {
    int y = 0;
    for(const auto &row : game_map.map_points) {
        int x = 0;
        for(const auto point : row) {
            if (point == MapPoint::WallFull) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 20 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::WallAbove) {
                SDL_Rect wall_rect{ x*20, y*20 ,20, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::WallBelow) {
                SDL_Rect wall_rect{ x*20, y*20 + 10, 20, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::WallLeft) {
                SDL_Rect wall_rect{ x*20, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::WallRight) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 ,10, 20 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::CornerTopLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::CornerTopRightInside) {
                SDL_Rect wall_rect{ x*20, y*20 + 10 ,10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::CornerBottomRightInside) {
                SDL_Rect wall_rect{ x*20,y*20 , 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::CornerBottomLeftInside) {
                SDL_Rect wall_rect{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
            } else if (point == MapPoint::CornerTopLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20 + 10, 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_small);
            } else if (point == MapPoint::CornerTopRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20 +10,10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_small);
            } else if (point == MapPoint::CornerBottomRightOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_small);
            } else if (point == MapPoint::CornerBottomLeftOutside) {
                SDL_Rect wall_rect_big{ x*20, y*20, 20, 20 };
                SDL_Rect wall_rect_small{ x*20 + 10, y*20, 10, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_big);
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0x00, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect_small);
            } else if (point == MapPoint::Fence) {
                SDL_Rect wall_rect{ x*20, y*20 + 10, 20, 10 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0xde, 0xa8, 0xdb, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &wall_rect);
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
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &dot_rect);
            } else if (point == MapObject::PowerPellet) {
                SDL_Rect dot_rect{ x*20 + 6, y*20 + 6, 12, 12 };
                SDL_SetRenderDrawColor(main_display.get_renderer(), 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(main_display.get_renderer(), &dot_rect);
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

void Game::check_collisions(PlayableCharacter& c) {
    if (c.is_grid_aligned()) {
        if (game_map.map_objects[c.pos_grid_y][c.pos_grid_x] == MapObject::Dot) {
            game_map.dots_remaining -= 1;
            game_map.map_objects[c.pos_grid_y][c.pos_grid_x] = MapObject::Nothing;
        }
    }
}