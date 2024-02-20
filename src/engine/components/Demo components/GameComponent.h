//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace engine::components {
    class GameComponent : public InputComponent, public events::Subject {
    public:
        explicit GameComponent(window::GameWindow *win);
        void tick(game::GameObject *gameObject, game::Game &game) override;
    };
}
// engine::components
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H
