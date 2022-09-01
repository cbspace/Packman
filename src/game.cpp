#include "game.h"

Game::Game() {
    quit_flag = false;
}

int Game::game_loop() {
    if(auto e = main_display.init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        cout << e.value().get_error_text() << endl;
        return 1;
    }

    if (auto e = main_display.load_map_from_file(MAP_PATH)) {
        cout << e.value().get_error_text() << endl;
        return 1;
    }

    return event_loop();
}

int Game::event_loop() {
    while (!quit_flag) {
        auto last_key_event = get_key();

        quit_flag = (last_key_event == KeyPress::Quit);

        SDL_Delay(16);
    }
    return 0;
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