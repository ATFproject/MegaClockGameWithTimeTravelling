//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace mcgwtt::components {
    class WindowMovementController
            : public engine::components::InputComponent {
    public:
        explicit WindowMovementController(window::GameWindow *win);
        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override;
        void onNotify(events::Type type) override;
        void onNotify(const events::Event *event) override;
    };
}
// engine::components
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWMOVEMENTCONTROLLER_H
