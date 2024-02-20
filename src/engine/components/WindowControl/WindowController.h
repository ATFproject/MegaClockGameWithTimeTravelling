//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace engine::components {
    class WindowController : public InputComponent, public events::Subject {
    public:
        explicit WindowController(window::GameWindow *win);
        void tick(game::GameObject *gameObject, game::Game &game) override;
    };
}
// engine::components

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLLER_H
