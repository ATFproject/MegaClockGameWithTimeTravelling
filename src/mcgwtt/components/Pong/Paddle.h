//
// Created by livefish on 3/2/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

namespace mcgwtt::components {
    class PaddleInput : public engine::components::InputComponent, public engine::events::Subject {
    public:
        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {

        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
