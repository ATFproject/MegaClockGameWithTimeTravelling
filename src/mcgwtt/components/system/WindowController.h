// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "engine/window/GameWindow.h"

namespace mcgwtt {
    class WindowController : public engine::components::InputComponent {
    public:
        explicit WindowController(window::GameWindow *win) {
            this->addObserver(win);
        }

        void tick(engine::game::Game &game) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                notify(window::WindowCloseEvent());
            }
        }
    };
}
// engine::components

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
