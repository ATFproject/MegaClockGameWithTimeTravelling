//
// Created by livefish on 2/20/24.
//

#include "WindowController.h"

namespace engine::components {
    WindowController::WindowController(window::GameWindow *win) {
        this->addObserver(win);
        sound = game::resources::load<sf::SoundBuffer>("music.mp3");
        static sf::Sound go;
        go.setBuffer(*sound);
        go.play();
    }

    void WindowController::tick(game::GameObject *gameObject, game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            notify(engine::events::Type::CLOSE);
        }
    }
}
