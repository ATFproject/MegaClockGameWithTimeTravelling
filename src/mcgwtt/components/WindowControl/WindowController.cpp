//
// Created by livefish on 2/20/24.
//

#include "WindowController.h"

namespace mcgwtt::components {
    WindowController::WindowController(window::GameWindow *win) {
        this->addObserver(win);
    }

    void WindowController::tick(engine::game::GameObject *gameObject, engine::game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            notify(events::Type::CLOSE);
        }
    }
}
