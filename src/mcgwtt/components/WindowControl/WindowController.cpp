//
// Created by livefish on 2/20/24.
//

#include "WindowController.h"
#include "GameWindow.h"

namespace mcgwtt::components {
    WindowController::WindowController(window::GameWindow *win, sf::RenderWindow *window) : _window(window) {
        this->addObserver(win);
    }

    void WindowController::tick(engine::game::GameObject *gameObject, engine::game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            notify(window::WindowCloseEvent());
        }
    }
    void WindowController::onNotify(const engine::events::Event &event) {
        ENGINE_CHECK_EVENT(engine::game::GameResizeEvent,
                           _window->setView(sf::View(
                                   sf::FloatRect(0.f, 0.f, e->_size.x, e->_size.y)
                           ));
        );
    }

}
