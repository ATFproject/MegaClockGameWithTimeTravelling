// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H

#include "components/ComponentInterface.h"
#include "window/GameWindow.h"

namespace mcgwtt {
    class WindowController : public engine::components::InputComponent {
    public:
        explicit WindowController(window::GameWindow *win);
        void tick(engine::game::Game &game) override;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
