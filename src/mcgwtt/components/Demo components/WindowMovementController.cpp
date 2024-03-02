//
// Created by livefish on 2/20/24.
//

#include "WindowMovementController.h"
#include "game/Game.h"

namespace mcgwtt::components {
    WindowMovementController::WindowMovementController(window::GameWindow *win) {
        this->addObserver(win);
    }

    void WindowMovementController::tick(engine::game::GameObject *gameObject, engine::game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            notify(std::shared_ptr<events::Event>(
                    new window::WindowMoveEvent(10, 0)
            ).get());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            notify(std::shared_ptr<events::Event>(
                    new window::WindowMoveEvent(-10, 0)
            ).get());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            notify(std::shared_ptr<events::Event>(
                    new window::WindowMoveEvent(0, -10)
            ).get());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            notify(std::shared_ptr<events::Event>(
                    new window::WindowMoveEvent(0, 10)
            ).get());
        }
    }

    void WindowMovementController::onNotify(events::Type type) {

    }

    void WindowMovementController::onNotify(const events::Event *event) {

    }
}

