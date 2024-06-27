// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H

#include "ComponentInterface.h"

namespace engine::components {
    class EmptyInputComponent : public InputComponent {
    public:
        void tick(game::Game &game) override {}
        void onNotify(const Event &event) override {}
    };

    class EmptyPhysicsComponent : public PhysicsComponent {
    public:
        void tick(game::Game &game) override {}
        void onNotify(const Event &event) override {}
    };

    class EmptyGraphicsComponent : public GraphicsComponent {
    public:
        void draw() override {};
        void onNotify(const Event &event) override {}
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H
