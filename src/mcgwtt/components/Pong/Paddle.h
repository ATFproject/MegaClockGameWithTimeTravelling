//
// Created by livefish on 3/2/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H

#include "components/ComponentInterface.h"
#include "observers/Subject.h"

namespace mcgwtt::components {
    class PaddleInput : public engine::components::InputComponent {
    public:
        void tick(engine::game::GameObject *gameObject, engine::game::Game &game) override {

        }

        void onNotify(events::Event *event) override {
            Observer::onNotify(event);
        }

        void onNotify(events::Type type) override {
            if (type == events::Type::CLOSE)
                std::cout << "BANANA!" << std::endl;
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PADDLE_H
