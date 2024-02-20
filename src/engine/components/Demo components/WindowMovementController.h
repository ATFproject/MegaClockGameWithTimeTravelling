//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace engine::components {
    class WindowMovementController : public InputComponent, public events::Subject {
    public:
        explicit WindowMovementController(window::GameWindow *win);
        void tick(game::GameObject *gameObject, game::Game &game) override;
    };
}
// engine::components
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H
