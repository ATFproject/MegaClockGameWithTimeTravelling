//
// Created by livefish on 5/23/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_LOADABLECOMPONENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_LOADABLECOMPONENTS_H

#include "components/ComponentInterface.h"

namespace mcgwtt {
    class LoadableGraphicsComponent : public engine::components::GraphicsComponent {
    private:
    public:
        void draw() override {
        }

        void onNotify(const engine::Event &event) override {
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_LOADABLECOMPONENTS_H
