//
// Created by livefish on 2/20/24.
//

#include "WindowMovementController.h"
#include "game/Game.h"

namespace mcgwtt {
    WindowMovementController::WindowMovementController(window::GameWindow *win) {
        this->addObserver(win);
    }

    void WindowMovementController::tick(engine::game::GameObject *gameObject, engine::game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            notify(window::WindowMoveEvent(10, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            notify(window::WindowMoveEvent(-10, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            notify(window::WindowMoveEvent(0, -10));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            notify(window::WindowMoveEvent(0, 10));
        }
    }
}

