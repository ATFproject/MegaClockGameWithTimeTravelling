// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "WindowController.h"

namespace mcgwtt {
    WindowController::WindowController(window::GameWindow *win) {
        this->addObserver(win);
    }

    void WindowController::tick(engine::game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            notify(window::WindowCloseEvent());
        }
    }
}