//
// Created by livefish on 3/10/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_MEMTEST_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_MEMTEST_H

#include "components/ComponentInterface.h"

namespace mcgwtt::components {
    class MemoryTest : public engine::components::GraphicsComponent {
    public:
        void draw(engine::game::GameObject *gameObject) override {
            std::vector<engine::Texture *> test(1000);
            for (int i = 0; i < 1000; ++i) {
                test.push_back(engine::resourceHandler.addRes(new engine::Texture("ground.png")));
            }
        }
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_MEMTEST_H
